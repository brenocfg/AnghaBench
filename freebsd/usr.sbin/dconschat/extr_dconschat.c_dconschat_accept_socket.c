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
struct kevent {int dummy; } ;
struct dcons_state {int flags; int /*<<< orphan*/  zero; int /*<<< orphan*/  kq; } ;
struct dcons_port {int port; int infd; int outfd; scalar_t__ skip_read; TYPE_1__* res; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sga ;
typedef  int /*<<< orphan*/  linemode ;
typedef  int /*<<< orphan*/  echo ;
typedef  int /*<<< orphan*/  bin ;
struct TYPE_2__ {int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_addrlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCONS_GDB ; 
 char DO ; 
 char DONT ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int F_TELNET ; 
 char IAC ; 
 scalar_t__ IS_CONSOLE (struct dcons_port*) ; 
 scalar_t__ IS_GDB (struct dcons_port*) ; 
 int /*<<< orphan*/  NOTE_LOWAT ; 
 int O_NDELAY ; 
 char TELOPT_BINARY ; 
 char TELOPT_ECHO ; 
 char TELOPT_LINEMODE ; 
 char TELOPT_SGA ; 
 char WILL ; 
 int accept (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dconschat_read_dcons (struct dcons_state*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static int
dconschat_accept_socket(struct dcons_state *dc, struct dcons_port *p)
{
	socklen_t addrlen;
	int ns, flags;
	struct kevent kev;

	/* accept connection */
	addrlen = p->res->ai_addrlen;
	ns = accept(p->s, p->res->ai_addr, &addrlen);
	if (ns < 0)
		err(1, "accept");
	if (verbose)
		printf("port%d accepted\n", p->port);

	flags = fcntl(ns, F_GETFL, 0);
	flags |= O_NDELAY;
	fcntl(ns, F_SETFL, flags);
#if 1
	if (IS_CONSOLE(p) && (dc->flags & F_TELNET) != 0) {
		char sga[] = {IAC, WILL, TELOPT_SGA};
		char linemode[] = {IAC, DONT, TELOPT_LINEMODE};
		char echo[] = {IAC, WILL, TELOPT_ECHO};
		char bin[] = {IAC, DO, TELOPT_BINARY};

		write(ns, sga, sizeof(sga));
		write(ns, linemode, sizeof(linemode));
		write(ns, echo, sizeof(echo));
		write(ns, bin, sizeof(bin));
		p->skip_read = 0;
	}
#endif
	/* discard backlog on GDB port */
	if (IS_GDB(p)) {
		char buf[2048];
		int len;

		while ((len = dconschat_read_dcons(dc, DCONS_GDB, &buf[0],
				 2048)) > 0)
			if (verbose)
				printf("discard %d chars on GDB port\n", len);
	}

	p->infd = p->outfd = ns;
	EV_SET(&kev, ns, EVFILT_READ, EV_ADD, NOTE_LOWAT, 1, (void *)p);
	kevent(dc->kq, &kev, 1, NULL, 0, &dc->zero);
	return(0);
}