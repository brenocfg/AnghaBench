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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  FD_CLR (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  FD_ISSET (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  RESOLVER_TIMEOUT ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int _rpc_dtablesize () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  resfd ; 
 int select (int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int svc_fds ; 
 int svc_fdset ; 
 int /*<<< orphan*/  svc_getreqset (int*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 scalar_t__ yp_pid ; 
 int /*<<< orphan*/  yp_prune_dnsq () ; 
 int /*<<< orphan*/  yp_run_dnsq () ; 

__attribute__((used)) static void
yp_svc_run(void)
{
#ifdef FD_SETSIZE
	fd_set readfds;
#else
	int readfds;
#endif /* def FD_SETSIZE */
	int fd_setsize = _rpc_dtablesize();
	struct timeval timeout;

	/* Establish the identity of the parent ypserv process. */
	yp_pid = getpid();

	for (;;) {
#ifdef FD_SETSIZE
		readfds = svc_fdset;
#else
		readfds = svc_fds;
#endif /* def FD_SETSIZE */

		FD_SET(resfd, &readfds);

		timeout.tv_sec = RESOLVER_TIMEOUT;
		timeout.tv_usec = 0;
		switch (select(fd_setsize, &readfds, NULL, NULL,
			       &timeout)) {
		case -1:
			if (errno == EINTR) {
				continue;
			}
			warn("svc_run: - select failed");
			return;
		case 0:
			if (getpid() == yp_pid)
				yp_prune_dnsq();
			break;
		default:
			if (getpid() == yp_pid) {
				if (FD_ISSET(resfd, &readfds)) {
					yp_run_dnsq();
					FD_CLR(resfd, &readfds);
				}
				svc_getreqset(&readfds);
			}
		}
		if (yp_pid != getpid())
			_exit(0);
	}
}