#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_DISCARD_CHECKPOINT ; 
 int dsl_early_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_checkpoint_discard_check ; 
 int /*<<< orphan*/  spa_checkpoint_discard_sync ; 

int
spa_checkpoint_discard(const char *pool)
{
	/*
	 * Similarly to spa_checkpoint(), we want our synctask to run
	 * before any pending dirty data are written to disk so they
	 * won't end up in the checkpoint's data structures (e.g.
	 * ms_checkpointing and vdev_checkpoint_sm) and re-create any
	 * space maps that the discarding open-context thread has
	 * deleted.
	 * [see spa_discard_checkpoint_sync and spa_discard_checkpoint_thread]
	 */
	return (dsl_early_sync_task(pool, spa_checkpoint_discard_check,
	    spa_checkpoint_discard_sync, NULL, 0,
	    ZFS_SPACE_CHECK_DISCARD_CHECKPOINT));
}