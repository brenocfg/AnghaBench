#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  other_sin ;

/* Variables and functions */
 int MAX_LONGS ; 
 int MAX_LOOPS ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,struct sockaddr*,int*) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 scalar_t__ check_buffer (long*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int listen (int,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recv (int,long*,int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srandom (long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcpstream_server(struct sockaddr_in sin, long seed)
{
	int i, j, listen_sock, accept_sock;
	struct sockaddr_in other_sin;
	long buffer[MAX_LONGS];
	socklen_t addrlen;
	ssize_t len;

	int input_byte_counter;

	listen_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_sock == -1)
		errx(-1, "socket: %s", strerror(errno));

	if (bind(listen_sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		errx(-1, "bind: %s", strerror(errno));

	if (listen(listen_sock, -1) == -1)
		errx(-1, "listen: %s", strerror(errno));

	while (1) {
		bzero(&other_sin, sizeof(other_sin));
		addrlen = sizeof(other_sin);

		accept_sock = accept(listen_sock, (struct sockaddr *)
		    &other_sin, &addrlen);
		if (accept_sock == -1) {
			perror("accept");
			continue;
		}
		printf("connection opened from %s:%d\n",
		    inet_ntoa(other_sin.sin_addr), ntohs(other_sin.sin_port));
		input_byte_counter = 0;

		srandom(seed);

		for (j = 0; j < MAX_LOOPS; j++) {
			for (i = 0; i < MAX_LONGS; i++) {
				len = recv(accept_sock, buffer,
				    i * sizeof(long), MSG_WAITALL);
				if (len != i * sizeof(long)) {
					perror("recv");
					goto done;
				}
				if (check_buffer(buffer, i) == 0) {
					fprintf(stderr,
    "Corruption in block beginning %d and ending %d\n", input_byte_counter,
    input_byte_counter + len);
					fprintf(stderr,
    "Block size %d\n", i * sizeof(long));
					goto done;
				}
				input_byte_counter += len;
			}
		}
done:
		printf("connection closed\n");
		close(accept_sock);
	}
}