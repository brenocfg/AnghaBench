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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int MAX_LONGS ; 
 int MAX_LOOPS ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_buffer (long*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int send (int,long*,int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srandom (long) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcpstream_client(struct sockaddr_in sin, long seed)
{
	long buffer[MAX_LONGS];
	ssize_t len;
	int i, j, sock;

	srandom(seed);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		errx(-1, "socket: %s", strerror(errno));

	if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) == -1)
		errx(-1, "connect: %s", strerror(errno));

	for (j = 0; j < MAX_LOOPS; j++) {
		for (i = 0; i < MAX_LONGS; i++) {
			fill_buffer(buffer, i);
			len = send(sock, buffer, i * sizeof(long), 0);
			if (len == -1) {
				printf("%d bytes written of %d expected\n",
				    len, i * sizeof(long));
				fflush(stdout);
				perror("send");
				goto done;
			}
		}
	}

done:
	close(sock);
}