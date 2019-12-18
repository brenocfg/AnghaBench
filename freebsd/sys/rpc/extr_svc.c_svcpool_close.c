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
struct TYPE_6__ {int /*<<< orphan*/  sg_lock; int /*<<< orphan*/  sg_state; } ;
struct TYPE_5__ {TYPE_2__* sp_groups; int /*<<< orphan*/  sp_lock; int /*<<< orphan*/  sp_state; } ;
typedef  TYPE_1__ SVCPOOL ;
typedef  TYPE_2__ SVCGROUP ;

/* Variables and functions */
 int /*<<< orphan*/  SVCPOOL_ACTIVE ; 
 int /*<<< orphan*/  SVCPOOL_INIT ; 
 int SVC_MAXGROUPS ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcpool_cleanup (TYPE_1__*) ; 

void
svcpool_close(SVCPOOL *pool)
{
	SVCGROUP *grp;
	int g;

	svcpool_cleanup(pool);

	/* Now, initialize the pool's state for a fresh svc_run() call. */
	mtx_lock(&pool->sp_lock);
	pool->sp_state = SVCPOOL_INIT;
	mtx_unlock(&pool->sp_lock);
	for (g = 0; g < SVC_MAXGROUPS; g++) {
		grp = &pool->sp_groups[g];
		mtx_lock(&grp->sg_lock);
		grp->sg_state = SVCPOOL_ACTIVE;
		mtx_unlock(&grp->sg_lock);
	}
}