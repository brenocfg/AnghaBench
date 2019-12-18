#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; scalar_t__ revents; } ;
struct TYPE_4__ {char* xp_netid; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 scalar_t__ debugging ; 
 TYPE_1__* find_rmtcallxprt_by_fd (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  handle_reply (int,TYPE_1__*) ; 
 int rpcb_rmtcalls ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
check_rmtcalls(struct pollfd *pfds, int nfds)
{
	int j, ncallbacks_found = 0, rmtcalls_pending;
	SVCXPRT *xprt;

	if (rpcb_rmtcalls == 0)
		return (0);

	rmtcalls_pending = rpcb_rmtcalls;
	for (j = 0; j < nfds; j++) {
		if ((xprt = find_rmtcallxprt_by_fd(pfds[j].fd)) != NULL) {
			if (pfds[j].revents) {
				ncallbacks_found++;
#ifdef DEBUG_RMTCALL
			if (debugging)
				fprintf(stderr,
"my_svc_run:  polled on forwarding fd %d, netid %s - calling handle_reply\n",
		pfds[j].fd, xprt->xp_netid);
#endif
				handle_reply(pfds[j].fd, xprt);
				pfds[j].revents = 0;
				if (ncallbacks_found >= rmtcalls_pending) {
					break;
				}
			}
		}
	}
	return (ncallbacks_found);
}