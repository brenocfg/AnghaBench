#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct socket {int so_options; int so_state; TYPE_2__* so_proto; scalar_t__ so_error; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int pr_flags; TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_connect ) (struct socket*,struct sockaddr*,struct thread*) ;int (* pru_connectat ) (int,struct socket*,struct sockaddr*,struct thread*) ;} ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int EISCONN ; 
 int EOPNOTSUPP ; 
 int PR_CONNREQUIRED ; 
 int SO_ACCEPTCONN ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int sodisconnect (struct socket*) ; 
 int stub1 (struct socket*,struct sockaddr*,struct thread*) ; 
 int stub2 (int,struct socket*,struct sockaddr*,struct thread*) ; 

int
soconnectat(int fd, struct socket *so, struct sockaddr *nam, struct thread *td)
{
	int error;

	if (so->so_options & SO_ACCEPTCONN)
		return (EOPNOTSUPP);

	CURVNET_SET(so->so_vnet);
	/*
	 * If protocol is connection-based, can only connect once.
	 * Otherwise, if connected, try to disconnect first.  This allows
	 * user to disconnect by connecting to, e.g., a null address.
	 */
	if (so->so_state & (SS_ISCONNECTED|SS_ISCONNECTING) &&
	    ((so->so_proto->pr_flags & PR_CONNREQUIRED) ||
	    (error = sodisconnect(so)))) {
		error = EISCONN;
	} else {
		/*
		 * Prevent accumulated error from previous connection from
		 * biting us.
		 */
		so->so_error = 0;
		if (fd == AT_FDCWD) {
			error = (*so->so_proto->pr_usrreqs->pru_connect)(so,
			    nam, td);
		} else {
			error = (*so->so_proto->pr_usrreqs->pru_connectat)(fd,
			    so, nam, td);
		}
	}
	CURVNET_RESTORE();

	return (error);
}