#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ vdev_id; int /*<<< orphan*/  vdev_removing; int /*<<< orphan*/ * vdev_mg; TYPE_2__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  spa_dsl_pool; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  metaslab_group_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SPA_ASYNC_INITIALIZE_RESTART ; 
 scalar_t__ TXG_CONCURRENT_STATES ; 
 scalar_t__ TXG_DEFER_SIZE ; 
 int /*<<< orphan*/  VDD_DTL ; 
 int /*<<< orphan*/  VDEV_INITIALIZE_ACTIVE ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NONE ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_assigned (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dsl_sync_task_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_group_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_group_passivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int spa_reset_logs (TYPE_2__*) ; 
 scalar_t__ spa_vdev_config_enter (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_vdev_config_exit (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_vdev_remove_top_check (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_dirty_leaves (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vdev_initialize_stop_all (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_remove_initiate_sync ; 

__attribute__((used)) static int
spa_vdev_remove_top(vdev_t *vd, uint64_t *txg)
{
	spa_t *spa = vd->vdev_spa;
	int error;

	/*
	 * Check for errors up-front, so that we don't waste time
	 * passivating the metaslab group and clearing the ZIL if there
	 * are errors.
	 */
	error = spa_vdev_remove_top_check(vd);
	if (error != 0)
		return (error);

	/*
	 * Stop allocating from this vdev.  Note that we must check
	 * that this is not the only device in the pool before
	 * passivating, otherwise we will not be able to make
	 * progress because we can't allocate from any vdevs.
	 * The above check for sufficient free space serves this
	 * purpose.
	 */
	metaslab_group_t *mg = vd->vdev_mg;
	metaslab_group_passivate(mg);

	/*
	 * Wait for the youngest allocations and frees to sync,
	 * and then wait for the deferral of those frees to finish.
	 */
	spa_vdev_config_exit(spa, NULL,
	    *txg + TXG_CONCURRENT_STATES + TXG_DEFER_SIZE, 0, FTAG);

	/*
	 * We must ensure that no "stubby" log blocks are allocated
	 * on the device to be removed.  These blocks could be
	 * written at any time, including while we are in the middle
	 * of copying them.
	 */
	error = spa_reset_logs(spa);

	/*
	 * We stop any initializing that is currently in progress but leave
	 * the state as "active". This will allow the initializing to resume
	 * if the removal is canceled sometime later.
	 */
	vdev_initialize_stop_all(vd, VDEV_INITIALIZE_ACTIVE);

	*txg = spa_vdev_config_enter(spa);

	/*
	 * Things might have changed while the config lock was dropped
	 * (e.g. space usage).  Check for errors again.
	 */
	if (error == 0)
		error = spa_vdev_remove_top_check(vd);

	if (error != 0) {
		metaslab_group_activate(mg);
		spa_async_request(spa, SPA_ASYNC_INITIALIZE_RESTART);
		return (error);
	}

	vd->vdev_removing = B_TRUE;

	vdev_dirty_leaves(vd, VDD_DTL, *txg);
	vdev_config_dirty(vd);
	dmu_tx_t *tx = dmu_tx_create_assigned(spa->spa_dsl_pool, *txg);
	dsl_sync_task_nowait(spa->spa_dsl_pool,
	    vdev_remove_initiate_sync,
	    (void *)(uintptr_t)vd->vdev_id, 0, ZFS_SPACE_CHECK_NONE, tx);
	dmu_tx_commit(tx);

	return (0);
}