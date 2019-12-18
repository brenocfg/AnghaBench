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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PORT1 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_1__) ; 
 scalar_t__ listen (int,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setup_tcp(const char *test, int *fdp, int port)
{
	fd_set writefds, exceptfds;
	struct sockaddr_in sin;
	int ret, sock1, sock2, sock3;
	struct timeval tv;

	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	/*
	 * First set up the listen socket.
	 */
	sin.sin_port = htons(port);
	sock1 = socket(PF_INET, SOCK_STREAM, 0);
	if (sock1 < 0)
		err(1, "%s: setup_tcp: socket", test);
	if (bind(sock1, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(1, "%s: bind(%s, %d)", test, inet_ntoa(sin.sin_addr),
		    PORT1);
	if (listen(sock1, -1) < 0)
		err(1, "%s: listen", test);

	/*
	 * Now connect to it, non-blocking so that we don't deadlock against
	 * ourselves.
	 */
	sock2 = socket(PF_INET, SOCK_STREAM, 0);
	if (sock2 < 0)
		err(1, "%s: setup_tcp: socket", test);
	if (fcntl(sock2, F_SETFL, O_NONBLOCK) < 0)
		err(1, "%s: setup_tcp: fcntl(O_NONBLOCK)", test);
	if (connect(sock2, (struct sockaddr *)&sin, sizeof(sin)) < 0 &&
	    errno != EINPROGRESS)
		err(1, "%s: setup_tcp: connect(%s, %d)", test,
		    inet_ntoa(sin.sin_addr), PORT1);

	/*
	 * Now pick up the connection after sleeping a moment to make sure
	 * there's been time for some packets to go back and forth.
	 */
	if (sleep(1) != 0)
		err(1, "%s: sleep(1)", test);
	sock3 = accept(sock1, NULL, NULL);
	if (sock3 < 0)
		err(1, "%s: accept", test);
	if (sleep(1) != 0)
		err(1, "%s: sleep(1)", test);

	FD_ZERO(&writefds);
	FD_SET(sock2, &writefds);
	FD_ZERO(&exceptfds);
	FD_SET(sock2, &exceptfds);
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	ret = select(sock2 + 1, NULL, &writefds, &exceptfds, &tv);
	if (ret < 0)
		err(1, "%s: setup_tcp: select", test);
	if (FD_ISSET(sock2, &exceptfds))
		errx(1, "%s: setup_tcp: select: exception", test);
	if (!FD_ISSET(sock2, &writefds))
		errx(1, "%s: setup_tcp: select: not writable", test);

	close(sock1);
	fdp[0] = sock2;
	fdp[1] = sock3;
}