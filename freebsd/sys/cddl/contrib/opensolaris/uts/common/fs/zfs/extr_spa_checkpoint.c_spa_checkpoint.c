#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  spa_vdev_top_lock; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NORMAL ; 
 int dsl_early_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_checkpoint_check ; 
 int /*<<< orphan*/  spa_checkpoint_sync ; 
 int /*<<< orphan*/  spa_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (TYPE_1__*) ; 
 int spa_open (char const*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
spa_checkpoint(const char *pool)
{
	int error;
	spa_t *spa;

	error = spa_open(pool, &spa, FTAG);
	if (error != 0)
		return (error);

	mutex_enter(&spa->spa_vdev_top_lock);

	/*
	 * Wait for current syncing txg to finish so the latest synced
	 * uberblock (spa_ubsync) has all the changes that we expect
	 * to see if we were to revert later to the checkpoint. In other
	 * words we want the checkpointed uberblock to include/reference
	 * all the changes that were pending at the time that we issued
	 * the checkpoint command.
	 */
	txg_wait_synced(spa_get_dsl(spa), 0);

	/*
	 * As the checkpointed uberblock references blocks from the previous
	 * txg (spa_ubsync) we want to ensure that are not freeing any of
	 * these blocks in the same txg that the following synctask will
	 * run. Thus, we run it as an early synctask, so the dirty changes
	 * that are synced to disk afterwards during zios and other synctasks
	 * do not reuse checkpointed blocks.
	 */
	error = dsl_early_sync_task(pool, spa_checkpoint_check,
	    spa_checkpoint_sync, NULL, 0, ZFS_SPACE_CHECK_NORMAL);

	mutex_exit(&spa->spa_vdev_top_lock);

	spa_close(spa, FTAG);
	return (error);
}