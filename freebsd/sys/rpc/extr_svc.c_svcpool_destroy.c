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
struct TYPE_6__ {int /*<<< orphan*/  sp_sysctl; scalar_t__ sp_rcache; int /*<<< orphan*/  sp_lock; TYPE_2__* sp_groups; } ;
typedef  TYPE_1__ SVCPOOL ;
typedef  TYPE_2__ SVCGROUP ;

/* Variables and functions */
 int /*<<< orphan*/  M_RPC ; 
 int SVC_MAXGROUPS ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replay_freecache (scalar_t__) ; 
 int /*<<< orphan*/  svcpool_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

void
svcpool_destroy(SVCPOOL *pool)
{
	SVCGROUP *grp;
	int g;

	svcpool_cleanup(pool);

	for (g = 0; g < SVC_MAXGROUPS; g++) {
		grp = &pool->sp_groups[g];
		mtx_destroy(&grp->sg_lock);
	}
	mtx_destroy(&pool->sp_lock);

	if (pool->sp_rcache)
		replay_freecache(pool->sp_rcache);

	sysctl_ctx_free(&pool->sp_sysctl);
	free(pool, M_RPC);
}