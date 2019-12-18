#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sg_lock; } ;
struct TYPE_6__ {scalar_t__ xp_registered; TYPE_2__* xp_group; } ;
typedef  TYPE_1__ SVCXPRT ;
typedef  TYPE_2__ SVCGROUP ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVC_RELEASE (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_unregister_locked (TYPE_1__*) ; 

void
xprt_unregister(SVCXPRT *xprt)
{
	SVCGROUP *grp = xprt->xp_group;

	mtx_lock(&grp->sg_lock);
	if (xprt->xp_registered == FALSE) {
		/* Already unregistered by another thread */
		mtx_unlock(&grp->sg_lock);
		return;
	}
	xprt_unregister_locked(xprt);
	mtx_unlock(&grp->sg_lock);

	SVC_RELEASE(xprt);
}