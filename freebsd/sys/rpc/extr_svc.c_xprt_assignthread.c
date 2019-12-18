#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ sg_state; scalar_t__ sg_lastcreatetime; scalar_t__ sg_threadcount; scalar_t__ sg_maxthreads; int /*<<< orphan*/  sg_idlethreads; int /*<<< orphan*/  sg_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_cond; TYPE_1__* st_xprt; } ;
struct TYPE_8__ {TYPE_2__* xp_thread; TYPE_3__* xp_group; } ;
typedef  TYPE_1__ SVCXPRT ;
typedef  TYPE_2__ SVCTHREAD ;
typedef  TYPE_3__ SVCGROUP ;

/* Variables and functions */
 int FALSE ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ SVCPOOL_ACTIVE ; 
 scalar_t__ SVCPOOL_THREADWANTED ; 
 int /*<<< orphan*/  SVC_ACQUIRE (TYPE_1__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_ilink ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static int
xprt_assignthread(SVCXPRT *xprt)
{
	SVCGROUP *grp = xprt->xp_group;
	SVCTHREAD *st;

	mtx_assert(&grp->sg_lock, MA_OWNED);
	st = LIST_FIRST(&grp->sg_idlethreads);
	if (st) {
		LIST_REMOVE(st, st_ilink);
		SVC_ACQUIRE(xprt);
		xprt->xp_thread = st;
		st->st_xprt = xprt;
		cv_signal(&st->st_cond);
		return (TRUE);
	} else {
		/*
		 * See if we can create a new thread. The
		 * actual thread creation happens in
		 * svc_run_internal because our locking state
		 * is poorly defined (we are typically called
		 * from a socket upcall). Don't create more
		 * than one thread per second.
		 */
		if (grp->sg_state == SVCPOOL_ACTIVE
		    && grp->sg_lastcreatetime < time_uptime
		    && grp->sg_threadcount < grp->sg_maxthreads) {
			grp->sg_state = SVCPOOL_THREADWANTED;
		}
	}
	return (FALSE);
}