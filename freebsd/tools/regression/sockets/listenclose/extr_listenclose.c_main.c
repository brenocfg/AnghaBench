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
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_1__) ; 
 scalar_t__ listen (int,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
main(void)
{
	int listen_sock, connect_sock;
	struct sockaddr_in sin;
	socklen_t len;
	u_short port;
	int arg;

	listen_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_sock == -1)
		errx(-1,
		    "socket(PF_INET, SOCK_STREAM, 0) for listen socket: %s",
		    strerror(errno));


	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sin.sin_port = 0;

	if (bind(listen_sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errx(-1, "bind(%s, %d) for listen socket: %s",
		    inet_ntoa(sin.sin_addr), 0, strerror(errno));

	len = sizeof(sin);
	if (getsockname(listen_sock, (struct sockaddr *)&sin, &len) < 0)
		errx(-1, "getsockname() for listen socket: %s",
		    strerror(errno));
	port = sin.sin_port;

	if (listen(listen_sock, -1) < 0)
		errx(-1, "listen() for listen socket: %s", strerror(errno));

	connect_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (connect_sock == -1)
		errx(-1, "socket(PF_INET, SOCK_STREAM, 0) for connect "
		    "socket: %s", strerror(errno));

	arg = O_NONBLOCK;
	if (fcntl(connect_sock, F_SETFL, &arg) < 0)
		errx(-1, "socket(PF_INET, SOCK_STREAM, 0) for connect socket"
		    ": %s", strerror(errno));

	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sin.sin_port = port;

	if (connect(connect_sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errx(-1, "connect() for connect socket: %s", strerror(errno));
	close(connect_sock);
	close(listen_sock);

	return (0);
}