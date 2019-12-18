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
 int MAX (int,int) ; 
 scalar_t__ PJDLOG_MODE_STD ; 
 int asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closefrom (int) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pjdlog_debug_get () ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pjdlog_mode_get () ; 
 int /*<<< orphan*/  proto_close (struct proto_conn*) ; 
 int proto_descriptor (struct proto_conn*) ; 
 int /*<<< orphan*/  proto_get (char*) ; 
 int /*<<< orphan*/  proto_send (struct proto_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tls_call_exec_server(struct proto_conn *sock, struct proto_conn *tcp)
{
	int startfd, sockfd, tcpfd, safefd;
	char *startfdstr, *debugstr;

	if (pjdlog_mode_get() == PJDLOG_MODE_STD)
		startfd = 3;
	else /* if (pjdlog_mode_get() == PJDLOG_MODE_SYSLOG) */
		startfd = 0;

	/* Declare that we are receiver. */
	proto_send(sock, NULL, 0);

	sockfd = proto_descriptor(sock);
	tcpfd = proto_descriptor(tcp);

	safefd = MAX(sockfd, tcpfd);
	safefd = MAX(safefd, startfd);
	safefd++;

	/* Move sockfd and tcpfd to safe numbers first. */
	if (dup2(sockfd, safefd) == -1)
		pjdlog_exit(EX_OSERR, "dup2() failed");
	proto_close(sock);
	sockfd = safefd;
	if (dup2(tcpfd, safefd + 1) == -1)
		pjdlog_exit(EX_OSERR, "dup2() failed");
	proto_close(tcp);
	tcpfd = safefd + 1;

	/* Move socketpair descriptor to descriptor number startfd. */
	if (dup2(sockfd, startfd) == -1)
		pjdlog_exit(EX_OSERR, "dup2() failed");
	(void)close(sockfd);
	/* Move tcp descriptor to descriptor number startfd + 1. */
	if (dup2(tcpfd, startfd + 1) == -1)
		pjdlog_exit(EX_OSERR, "dup2() failed");
	(void)close(tcpfd);

	closefrom(startfd + 2);

	/*
	 * Even if FD_CLOEXEC was set on descriptors before dup2(), it should
	 * have been cleared on dup2(), but better be safe than sorry.
	 */
	if (fcntl(startfd, F_SETFD, 0) == -1)
		pjdlog_exit(EX_OSERR, "fcntl() failed");
	if (fcntl(startfd + 1, F_SETFD, 0) == -1)
		pjdlog_exit(EX_OSERR, "fcntl() failed");

	if (asprintf(&startfdstr, "%d", startfd) == -1)
		pjdlog_exit(EX_TEMPFAIL, "asprintf() failed");
	if (asprintf(&debugstr, "%d", pjdlog_debug_get()) == -1)
		pjdlog_exit(EX_TEMPFAIL, "asprintf() failed");

	execl(proto_get("execpath"), proto_get("execpath"), "proto", "tls",
	    proto_get("user"), "server", startfdstr, proto_get("tls:keyfile"),
	    proto_get("tls:certfile"), debugstr, NULL);
	pjdlog_exit(EX_SOFTWARE, "execl() failed");
}