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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct kevent {uintptr_t ident; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int EV_ADD ; 
 int EV_CLEAR ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NOSIGPIPE ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int accept (uintptr_t,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int bind (int,struct sockaddr*,int) ; 
 int close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  htons (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int kevent (int,struct kevent*,int,struct kevent*,int,int /*<<< orphan*/ *) ; 
 int kqueue () ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main()
{
	struct sockaddr_in addr;
	struct kevent ev[2];
	socklen_t socklen;
	int kq, sock, opt, pid, nev, fd;

	if ((kq = kqueue()) == -1)
		err(1, "kqueue");

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		err(1, "socket");

	EV_SET(&ev[0], sock, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, NULL);
	EV_SET(&ev[1], sock, EVFILT_WRITE, EV_ADD | EV_CLEAR, 0, 0, NULL);

	opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, &opt, sizeof(opt)) == -1)
		err(1, "setsockopt");

	if (kevent(kq, ev, 2, NULL, 0, NULL) == -1)
	    err(1, "kevent");

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		err(1, "setsockopt");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10000);

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		err(1, "bind");
	if (listen(sock, 0x80) == -1)
		err(1, "listen");

	if (ioctl(sock, FIONBIO, &opt) == -1)
		err(1, "ioctl(FIONBIO)");

	if (kevent(kq, ev, 2, NULL, 0, NULL) == -1)
		err(1, "kevent");

	pid = fork();
	if (pid == -1)
		err(1, "fork");
	if (pid == 0) {
		if (close(sock) == -1)
			err(1, "close");
		if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
			err(1, "socket");
		if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
			err(1, "connect");
	} else {
		nev = kevent(kq, NULL, 0, ev, 2, NULL);
		if (nev < 1)
			err(1, "kevent");
		for (int i = 0; i < nev; ++i) {
			if (ev[i].ident == (uintptr_t )sock) {
				fd = accept(ev[i].ident,
				    (struct sockaddr *)&addr, &socklen);
				if (fd == -1)
					err(1, "accept");
				printf("OK\n");
			}
		}
	}
}