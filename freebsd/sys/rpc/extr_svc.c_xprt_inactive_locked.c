#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sg_active; int /*<<< orphan*/  sg_lock; } ;
struct TYPE_5__ {scalar_t__ xp_active; int /*<<< orphan*/ * xp_thread; TYPE_2__* xp_group; } ;
typedef  TYPE_1__ SVCXPRT ;
typedef  TYPE_2__ SVCGROUP ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xp_alink ; 

void
xprt_inactive_locked(SVCXPRT *xprt)
{
	SVCGROUP *grp = xprt->xp_group;

	mtx_assert(&grp->sg_lock, MA_OWNED);
	if (xprt->xp_active) {
		if (xprt->xp_thread == NULL)
			TAILQ_REMOVE(&grp->sg_active, xprt, xp_alink);
		xprt->xp_active = FALSE;
	}
}