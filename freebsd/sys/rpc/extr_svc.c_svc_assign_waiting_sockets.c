#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sg_lock; int /*<<< orphan*/  sg_active; } ;
struct TYPE_4__ {int sp_groupcount; TYPE_2__* sp_groups; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;
typedef  TYPE_1__ SVCPOOL ;
typedef  TYPE_2__ SVCGROUP ;

/* Variables and functions */
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xp_alink ; 
 scalar_t__ xprt_assignthread (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
svc_assign_waiting_sockets(SVCPOOL *pool)
{
	SVCGROUP *grp;
	SVCXPRT *xprt;
	int g;

	for (g = 0; g < pool->sp_groupcount; g++) {
		grp = &pool->sp_groups[g];
		mtx_lock(&grp->sg_lock);
		while ((xprt = TAILQ_FIRST(&grp->sg_active)) != NULL) {
			if (xprt_assignthread(xprt))
				TAILQ_REMOVE(&grp->sg_active, xprt, xp_alink);
			else
				break;
		}
		mtx_unlock(&grp->sg_lock);
	}
}