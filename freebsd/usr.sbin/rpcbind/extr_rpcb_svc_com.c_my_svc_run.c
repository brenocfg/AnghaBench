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
struct pollfd {int fd; int /*<<< orphan*/  revents; void* events; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 void* MASKVAL ; 
 int /*<<< orphan*/  __svc_clean_idle (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int check_rmtcalls (struct pollfd*,size_t) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ debugging ; 
 scalar_t__ doterminate ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int poll (struct pollfd*,size_t,int) ; 
 int /*<<< orphan*/  rpcbindlockfd ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  svc_fdset ; 
 int /*<<< orphan*/  svc_getreq_poll (struct pollfd*,int) ; 
 int svc_maxfd ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 
 int terminate_rfd ; 
 int /*<<< orphan*/  write_warmstart () ; 

void
my_svc_run(void)
{
	size_t nfds;
	struct pollfd pollfds[FD_SETSIZE + 1];
	int poll_ret, check_ret;
	int n;
#ifdef SVC_RUN_DEBUG
	int i;
#endif
	register struct pollfd	*p;
	fd_set cleanfds;

	for (;;) {
		p = pollfds;
		p->fd = terminate_rfd;
		p->events = MASKVAL;
		p++;
		for (n = 0; n <= svc_maxfd; n++) {
			if (FD_ISSET(n, &svc_fdset)) {
				p->fd = n;
				p->events = MASKVAL;
				p++;
			}
		}
		nfds = p - pollfds;
		poll_ret = 0;
#ifdef SVC_RUN_DEBUG
		if (debugging) {
			fprintf(stderr, "polling for read on fd < ");
			for (i = 0, p = pollfds; i < nfds; i++, p++)
				if (p->events)
					fprintf(stderr, "%d ", p->fd);
			fprintf(stderr, ">\n");
		}
#endif
		poll_ret = poll(pollfds, nfds, 30 * 1000);

		if (doterminate != 0) {
			close(rpcbindlockfd);
#ifdef WARMSTART
			syslog(LOG_ERR,
			    "rpcbind terminating on signal %d. Restart with \"rpcbind -w\"",
			    (int)doterminate);
			write_warmstart();	/* Dump yourself */
#endif
			exit(2);
		}

		switch (poll_ret) {
		case -1:
			/*
			 * We ignore all errors, continuing with the assumption
			 * that it was set by the signal handlers (or any
			 * other outside event) and not caused by poll().
			 */
		case 0:
			cleanfds = svc_fdset;
			__svc_clean_idle(&cleanfds, 30, FALSE);
			continue;
		default:
#ifdef SVC_RUN_DEBUG
			if (debugging) {
				fprintf(stderr, "poll returned read fds < ");
				for (i = 0, p = pollfds; i < nfds; i++, p++)
					if (p->revents)
						fprintf(stderr, "%d ", p->fd);
				fprintf(stderr, ">\n");
			}
#endif
			/*
			 * If we found as many replies on callback fds
			 * as the number of descriptors selectable which
			 * poll() returned, there can be no more so we
			 * don't call svc_getreq_poll.  Otherwise, there
			 * must be another so we must call svc_getreq_poll.
			 */
			if ((check_ret = check_rmtcalls(pollfds, nfds)) ==
			    poll_ret)
				continue;
			svc_getreq_poll(pollfds, poll_ret-check_ret);
		}
#ifdef SVC_RUN_DEBUG
		if (debugging) {
			fprintf(stderr, "svc_maxfd now %u\n", svc_maxfd);
		}
#endif
	}
}