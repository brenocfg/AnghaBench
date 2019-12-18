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
struct tls_ctx {int tls_wait_called; int /*<<< orphan*/  tls_magic; int /*<<< orphan*/  tls_side; int /*<<< orphan*/ * tls_tcp; struct proto_conn* tls_sock; } ;
struct proto_conn {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int RFFDG ; 
 int RFPROC ; 
 int RFTSIGFLAGS (int /*<<< orphan*/ ) ; 
 int RFTSIGZMB ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  TLS_CTX_MAGIC ; 
 int /*<<< orphan*/  TLS_SIDE_CLIENT ; 
 struct tls_ctx* calloc (int,int) ; 
 int errno ; 
 int fork () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*) ; 
 int /*<<< orphan*/  proto_close (struct proto_conn*) ; 
 int proto_connect (int /*<<< orphan*/ *,char*,int,struct proto_conn**) ; 
 int /*<<< orphan*/  proto_send (struct proto_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rfork (int) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  tls_call_exec_client (struct proto_conn*,char const*,char const*,int) ; 
 int /*<<< orphan*/  tls_close (struct tls_ctx*) ; 
 int tls_connect_wait (struct tls_ctx*,int) ; 

__attribute__((used)) static int
tls_connect(const char *srcaddr, const char *dstaddr, int timeout, void **ctxp)
{
	struct tls_ctx *tlsctx;
	struct proto_conn *sock;
	pid_t pid;
	int error;

	PJDLOG_ASSERT(srcaddr == NULL || srcaddr[0] != '\0');
	PJDLOG_ASSERT(dstaddr != NULL);
	PJDLOG_ASSERT(timeout >= -1);
	PJDLOG_ASSERT(ctxp != NULL);

	if (strncmp(dstaddr, "tls://", 6) != 0)
		return (-1);
	if (srcaddr != NULL && strncmp(srcaddr, "tls://", 6) != 0)
		return (-1);

	if (proto_connect(NULL, "socketpair://", -1, &sock) == -1)
		return (errno);

#if 0
	/*
	 * We use rfork() with the following flags to disable SIGCHLD
	 * delivery upon the sandbox process exit.
	 */
	pid = rfork(RFFDG | RFPROC | RFTSIGZMB | RFTSIGFLAGS(0));
#else
	/*
	 * We don't use rfork() to be able to log information about sandbox
	 * process exiting.
	 */
	pid = fork();
#endif
	switch (pid) {
	case -1:
		/* Failure. */
		error = errno;
		proto_close(sock);
		return (error);
	case 0:
		/* Child. */
		pjdlog_prefix_set("[TLS sandbox] (client) ");
#ifdef HAVE_SETPROCTITLE
		setproctitle("[TLS sandbox] (client) ");
#endif
		tls_call_exec_client(sock, srcaddr, dstaddr, timeout);
		/* NOTREACHED */
	default:
		/* Parent. */
		tlsctx = calloc(1, sizeof(*tlsctx));
		if (tlsctx == NULL) {
			error = errno;
			proto_close(sock);
			(void)kill(pid, SIGKILL);
			return (error);
		}
		proto_send(sock, NULL, 0);
		tlsctx->tls_sock = sock;
		tlsctx->tls_tcp = NULL;
		tlsctx->tls_side = TLS_SIDE_CLIENT;
		tlsctx->tls_wait_called = false;
		tlsctx->tls_magic = TLS_CTX_MAGIC;
		if (timeout >= 0) {
			error = tls_connect_wait(tlsctx, timeout);
			if (error != 0) {
				(void)kill(pid, SIGKILL);
				tls_close(tlsctx);
				return (error);
			}
		}
		*ctxp = tlsctx;
		return (0);
	}
}