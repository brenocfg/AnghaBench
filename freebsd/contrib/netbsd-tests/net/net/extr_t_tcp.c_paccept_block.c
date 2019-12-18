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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int ssize_t ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EINTR ; 
 scalar_t__ EISCONN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FAIL (char*,...) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SIGALRM ; 
 int SOCK_NONBLOCK ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  alarm (int) ; 
 int bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  ding ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int paccept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
paccept_block(bool pacceptblock, bool fcntlblock)
{
	int srvr = -1, clnt = -1, as = -1;
	int ok, fl;
	ssize_t n;
	char buf[10];
	struct sockaddr_in sin, ba;
	struct sigaction sa;

	srvr = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (srvr == -1)
		FAIL("socket");

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
#ifdef BSD4_4
	sin.sin_len = sizeof(sin);
#endif
	sin.sin_port = htons(0);
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	ok = bind(srvr, (const struct sockaddr *)&sin, (socklen_t)sizeof(sin));
	if (ok == -1)
		FAIL("bind");

	socklen_t addrlen = sizeof(struct sockaddr_in);
	ok = getsockname(srvr, (struct sockaddr *)&ba, &addrlen);
	if (ok == -1)
		FAIL("getsockname");

	ok = listen(srvr, SOMAXCONN);
	if (ok == -1)
		FAIL("listen");

	clnt = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (clnt == -1)
		FAIL("socket");

	/* may not connect first time */
	ok = connect(clnt, (struct sockaddr *) &ba, addrlen);
	if (ok != -1 || errno != EINPROGRESS)
		FAIL("expected connect to fail");
	as = paccept(srvr, NULL, NULL, NULL, pacceptblock ? 0 : SOCK_NONBLOCK);
	ok = connect(clnt, (struct sockaddr *) &ba, addrlen);
	if (ok == -1 && errno != EISCONN)
		FAIL("connect failed");

#if 0
	fl = fcntl(srvr, F_GETFL, 0);
	if (fl == -1)
		FAIL("fnctl getfl");

	ok = fcntl(srvr, F_SETFL, fl & ~O_NONBLOCK);
	if (ok == -1)
		FAIL("fnctl setfl");
#endif

	if (as == -1) {		/* not true under NetBSD */
		as = paccept(srvr, NULL, NULL, NULL, pacceptblock ? 0 : SOCK_NONBLOCK);
		if (as == -1)
			FAIL("paccept");
	}
	if (fcntlblock) {
		fl = fcntl(as, F_GETFL, 0);
		if (fl == -1)
			FAIL("fnctl");
		if (fl != (O_RDWR|O_NONBLOCK))
			FAIL("fl 0x%x != 0x%x\n", fl, O_RDWR|O_NONBLOCK);
		ok = fcntl(as, F_SETFL, fl & ~O_NONBLOCK);
		if (ok == -1)
			FAIL("fnctl setfl");

		fl = fcntl(as, F_GETFL, 0);
		if (fl & O_NONBLOCK)
			FAIL("fl non blocking after reset");
	}
	sa.sa_handler = ding;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);
	alarm(1);
	n = read(as, buf, 10);

	if (pacceptblock || fcntlblock) {
		if (n == -1 && errno != EINTR)
			FAIL("read");
	} else {
		if (n != -1 || errno != EWOULDBLOCK)
			FAIL("read");
	}
	return;
fail:
	close(srvr);
	close(clnt);
	close(as);
}