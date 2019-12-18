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
struct socket {int so_state; scalar_t__ so_type; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  so_vnet; int /*<<< orphan*/  so_error; struct protosw* so_proto; } ;
struct protosw {TYPE_1__* pr_usrreqs; } ;
struct TYPE_2__ {int (* pru_shutdown ) (struct socket*) ;int /*<<< orphan*/  (* pru_flush ) (struct socket*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECONNABORTED ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int SHUT_RD ; 
 int SHUT_RDWR ; 
 int SHUT_WR ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOLISTENING (struct socket*) ; 
 int /*<<< orphan*/  SOLISTEN_LOCK (struct socket*) ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_ISDISCONNECTING ; 
 int /*<<< orphan*/  solisten_wakeup (struct socket*) ; 
 int /*<<< orphan*/  sorflush (struct socket*) ; 
 int /*<<< orphan*/  stub1 (struct socket*,int) ; 
 int stub2 (struct socket*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
soshutdown(struct socket *so, int how)
{
	struct protosw *pr = so->so_proto;
	int error, soerror_enotconn;

	if (!(how == SHUT_RD || how == SHUT_WR || how == SHUT_RDWR))
		return (EINVAL);

	soerror_enotconn = 0;
	if ((so->so_state &
	    (SS_ISCONNECTED | SS_ISCONNECTING | SS_ISDISCONNECTING)) == 0) {
		/*
		 * POSIX mandates us to return ENOTCONN when shutdown(2) is
		 * invoked on a datagram sockets, however historically we would
		 * actually tear socket down. This is known to be leveraged by
		 * some applications to unblock process waiting in recvXXX(2)
		 * by other process that it shares that socket with. Try to meet
		 * both backward-compatibility and POSIX requirements by forcing
		 * ENOTCONN but still asking protocol to perform pru_shutdown().
		 */
		if (so->so_type != SOCK_DGRAM && !SOLISTENING(so))
			return (ENOTCONN);
		soerror_enotconn = 1;
	}

	if (SOLISTENING(so)) {
		if (how != SHUT_WR) {
			SOLISTEN_LOCK(so);
			so->so_error = ECONNABORTED;
			solisten_wakeup(so);	/* unlocks so */
		}
		goto done;
	}

	CURVNET_SET(so->so_vnet);
	if (pr->pr_usrreqs->pru_flush != NULL)
		(*pr->pr_usrreqs->pru_flush)(so, how);
	if (how != SHUT_WR)
		sorflush(so);
	if (how != SHUT_RD) {
		error = (*pr->pr_usrreqs->pru_shutdown)(so);
		wakeup(&so->so_timeo);
		CURVNET_RESTORE();
		return ((error == 0 && soerror_enotconn) ? ENOTCONN : error);
	}
	wakeup(&so->so_timeo);
	CURVNET_RESTORE();

done:
	return (soerror_enotconn ? ENOTCONN : 0);
}