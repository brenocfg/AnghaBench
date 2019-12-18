#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {int sin_len; scalar_t__ sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sock ;

/* Variables and functions */
 void* AF_INET ; 
 scalar_t__ EBADF ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  PF_INET ; 
 scalar_t__ SHUT_RD ; 
 scalar_t__ SHUT_RDWR ; 
 scalar_t__ SHUT_WR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_1__) ; 
 scalar_t__ listen (int,int) ; 
 int shutdown (int,scalar_t__) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

int
main(void)
{
	struct sockaddr_in sock;
	socklen_t len;
	int listen_sock, connect_sock;
	u_short port;

	listen_sock = -1;

	/* Shutdown(2) on an invalid file descriptor has to return EBADF. */
	if ((shutdown(listen_sock, SHUT_RDWR) != -1) && (errno != EBADF))
		errx(-1, "shutdown() for invalid file descriptor does not "
		    "return EBADF");

	listen_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_sock == -1)
		errx(-1,
		    "socket(PF_INET, SOCK_STREAM, 0) for listen socket: %s",
		    strerror(errno));

	bzero(&sock, sizeof(sock));
	sock.sin_len = sizeof(sock);
	sock.sin_family = AF_INET;
	sock.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sock.sin_port = 0;

	if (bind(listen_sock, (struct sockaddr *)&sock, sizeof(sock)) < 0)
		errx(-1, "bind(%s, %d) for listen socket: %s",
		    inet_ntoa(sock.sin_addr), sock.sin_port, strerror(errno));

	len = sizeof(sock);
	if (getsockname(listen_sock, (struct sockaddr *)&sock, &len) < 0)
		errx(-1, "getsockname() for listen socket: %s",
		    strerror(errno));
	port = sock.sin_port;

	if (listen(listen_sock, -1) < 0)
		errx(-1, "listen() for listen socket: %s", strerror(errno));

	connect_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (connect_sock == -1)
		errx(-1, "socket(PF_INET, SOCK_STREAM, 0) for connect "
		    "socket: %s", strerror(errno));

	bzero(&sock, sizeof(sock));
	sock.sin_len = sizeof(sock);
	sock.sin_family = AF_INET;
	sock.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sock.sin_port = port;

	if (connect(connect_sock, (struct sockaddr *)&sock, sizeof(sock)) < 0)
		errx(-1, "connect() for connect socket: %s", strerror(errno));
	/* Try to pass an invalid flags. */
	if ((shutdown(connect_sock, SHUT_RD - 1) != -1) && (errno != EINVAL))
		errx(-1, "shutdown(SHUT_RD - 1) does not return EINVAL");
	if ((shutdown(connect_sock, SHUT_RDWR + 1) != -1) && (errno != EINVAL))
		errx(-1, "shutdown(SHUT_RDWR + 1) does not return EINVAL");

	if (shutdown(connect_sock, SHUT_RD) < 0)
		errx(-1, "shutdown(SHUT_RD) for connect socket: %s",
		    strerror(errno));
	if (shutdown(connect_sock, SHUT_WR) < 0)
		errx(-1, "shutdown(SHUT_WR) for connect socket: %s",
		    strerror(errno));

	close(connect_sock);
	close(listen_sock);

	return (0);
}