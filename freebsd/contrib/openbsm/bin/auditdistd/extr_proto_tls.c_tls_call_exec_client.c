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
struct proto_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/  F_SETFD ; 
 scalar_t__ PJDLOG_MODE_STD ; 
 int TLS_DEFAULT_TIMEOUT ; 
 int asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  closefrom (int) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pjdlog_debug_get () ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pjdlog_mode_get () ; 
 int /*<<< orphan*/  proto_close (struct proto_conn*) ; 
 int proto_descriptor (struct proto_conn*) ; 
 int /*<<< orphan*/  proto_get (char*) ; 
 int /*<<< orphan*/  proto_recv (struct proto_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tls_call_exec_client(struct proto_conn *sock, const char *srcaddr,
    const char *dstaddr, int timeout)
{
	char *timeoutstr, *startfdstr, *debugstr;
	int startfd;

	/* Declare that we are receiver. */
	proto_recv(sock, NULL, 0);

	if (pjdlog_mode_get() == PJDLOG_MODE_STD)
		startfd = 3;
	else /* if (pjdlog_mode_get() == PJDLOG_MODE_SYSLOG) */
		startfd = 0;

	if (proto_descriptor(sock) != startfd) {
		/* Move socketpair descriptor to descriptor number startfd. */
		if (dup2(proto_descriptor(sock), startfd) == -1)
			pjdlog_exit(EX_OSERR, "dup2() failed");
		proto_close(sock);
	} else {
		/*
		 * The FD_CLOEXEC is cleared by dup2(2), so when we not
		 * call it, we have to clear it by hand in case it is set.
		 */
		if (fcntl(startfd, F_SETFD, 0) == -1)
			pjdlog_exit(EX_OSERR, "fcntl() failed");
	}

	closefrom(startfd + 1);

	if (asprintf(&startfdstr, "%d", startfd) == -1)
		pjdlog_exit(EX_TEMPFAIL, "asprintf() failed");
	if (timeout == -1)
		timeout = TLS_DEFAULT_TIMEOUT;
	if (asprintf(&timeoutstr, "%d", timeout) == -1)
		pjdlog_exit(EX_TEMPFAIL, "asprintf() failed");
	if (asprintf(&debugstr, "%d", pjdlog_debug_get()) == -1)
		pjdlog_exit(EX_TEMPFAIL, "asprintf() failed");

	execl(proto_get("execpath"), proto_get("execpath"), "proto", "tls",
	    proto_get("user"), "client", startfdstr,
	    srcaddr == NULL ? "" : srcaddr, dstaddr,
	    proto_get("tls:fingerprint"), proto_get("tcp:port"), timeoutstr,
	    debugstr, NULL);
	pjdlog_exit(EX_SOFTWARE, "execl() failed");
}