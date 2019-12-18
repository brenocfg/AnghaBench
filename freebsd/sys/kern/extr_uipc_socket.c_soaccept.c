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
struct socket {int so_state; TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_accept ) (struct socket*,struct sockaddr**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int SS_NOFDREF ; 
 int stub1 (struct socket*,struct sockaddr**) ; 

int
soaccept(struct socket *so, struct sockaddr **nam)
{
	int error;

	SOCK_LOCK(so);
	KASSERT((so->so_state & SS_NOFDREF) != 0, ("soaccept: !NOFDREF"));
	so->so_state &= ~SS_NOFDREF;
	SOCK_UNLOCK(so);

	CURVNET_SET(so->so_vnet);
	error = (*so->so_proto->pr_usrreqs->pru_accept)(so, nam);
	CURVNET_RESTORE();
	return (error);
}