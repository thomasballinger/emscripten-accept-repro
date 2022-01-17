// When this program is compiled with
// emcc test.c -o test.js -lwebsocket.js -s NODERAWFS=1
// after installing the ws module with 
// npm install
// it fails with
// TypeError: Cannot read property 'stream' of undefined

// reference:
// https://emscripten.org/docs/porting/networking.html

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
        printf("main start\n");
        struct sockaddr_in my_addr, peer_addr;
        socklen_t peer_addr_size;
        int sd, b, l, acc;
        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(8000);
        inet_aton("127.0.0.1", &my_addr.sin_addr);

        sd = socket(AF_INET, SOCK_STREAM, 0);

        b = bind(sd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in));
        if(b > 0)
                printf("Binding Error\n");
        else
                printf("Binded Successfully\n");

        l = listen(sd, 1);
        if(l > 0)
                printf("Not listening\n");
        else {
                printf("Listening on %u...\n", ntohs(my_addr.sin_port));
        }
        peer_addr_size = sizeof(struct sockaddr_in);

        printf("calling accept...\n");
        acc = accept(sd, (struct sockaddr *)&peer_addr, &peer_addr_size);
        printf("...accept returned\n");

        if(acc > 0)
                printf("Accepted\n");
        else
                printf("Not accepted\n");
}
