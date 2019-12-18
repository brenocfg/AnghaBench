#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  vdev_state_dirty_node; scalar_t__ vdev_leaf_zap; scalar_t__ vdev_removing; TYPE_3__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  svr_lock; int /*<<< orphan*/  svr_cv; int /*<<< orphan*/ * svr_thread; int /*<<< orphan*/  svr_zaplist; } ;
typedef  TYPE_2__ spa_vdev_removal_t ;
struct TYPE_14__ {int /*<<< orphan*/  spa_dsl_pool; TYPE_2__* spa_vdev_removal; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NONE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_assigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_sync_task_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_alloc () ; 
 int /*<<< orphan*/  list_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* vdev_add_parent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_compact_children (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_indirect_ops ; 
 int /*<<< orphan*/  vdev_remove_child (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_remove_complete_sync ; 
 int /*<<< orphan*/  vdev_remove_enlist_zaps (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_remove_replace_with_indirect(vdev_t *vd, uint64_t txg)
{
	vdev_t *ivd;
	dmu_tx_t *tx;
	spa_t *spa = vd->vdev_spa;
	spa_vdev_removal_t *svr = spa->spa_vdev_removal;

	/*
	 * First, build a list of leaf zaps to be destroyed.
	 * This is passed to the sync context thread,
	 * which does the actual unlinking.
	 */
	svr->svr_zaplist = fnvlist_alloc();
	vdev_remove_enlist_zaps(vd, svr->svr_zaplist);

	ivd = vdev_add_parent(vd, &vdev_indirect_ops);
	ivd->vdev_removing = 0;

	vd->vdev_leaf_zap = 0;

	vdev_remove_child(ivd, vd);
	vdev_compact_children(ivd);

	ASSERT(!list_link_active(&vd->vdev_state_dirty_node));

	tx = dmu_tx_create_assigned(spa->spa_dsl_pool, txg);
	dsl_sync_task_nowait(spa->spa_dsl_pool, vdev_remove_complete_sync, svr,
	    0, ZFS_SPACE_CHECK_NONE, tx);
	dmu_tx_commit(tx);

	/*
	 * Indicate that this thread has exited.
	 * After this, we can not use svr.
	 */
	mutex_enter(&svr->svr_lock);
	svr->svr_thread = NULL;
	cv_broadcast(&svr->svr_cv);
	mutex_exit(&svr->svr_lock);
}