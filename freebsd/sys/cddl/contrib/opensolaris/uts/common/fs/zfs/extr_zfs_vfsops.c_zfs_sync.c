#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * z_log; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct TYPE_10__ {TYPE_1__* vfs_data; } ;
typedef  TYPE_2__ vfs_t ;
struct TYPE_11__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_3__ dsl_pool_t ;

/* Variables and functions */
 int MNT_LAZY ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_1__*) ; 
 TYPE_3__* dmu_objset_pool (int /*<<< orphan*/ ) ; 
 scalar_t__ panicstr ; 
 scalar_t__ spa_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_sync_allpools () ; 
 scalar_t__ sys_shutdown ; 
 int vfs_stdsync (TYPE_2__*,int) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_sync(vfs_t *vfsp, int waitfor)
{

	/*
	 * Data integrity is job one.  We don't want a compromised kernel
	 * writing to the storage pool, so we never sync during panic.
	 */
	if (panicstr)
		return (0);

	/*
	 * Ignore the system syncher.  ZFS already commits async data
	 * at zfs_txg_timeout intervals.
	 */
	if (waitfor == MNT_LAZY)
		return (0);

	if (vfsp != NULL) {
		/*
		 * Sync a specific filesystem.
		 */
		zfsvfs_t *zfsvfs = vfsp->vfs_data;
		dsl_pool_t *dp;
		int error;

		error = vfs_stdsync(vfsp, waitfor);
		if (error != 0)
			return (error);

		ZFS_ENTER(zfsvfs);
		dp = dmu_objset_pool(zfsvfs->z_os);

		/*
		 * If the system is shutting down, then skip any
		 * filesystems which may exist on a suspended pool.
		 */
		if (sys_shutdown && spa_suspended(dp->dp_spa)) {
			ZFS_EXIT(zfsvfs);
			return (0);
		}

		if (zfsvfs->z_log != NULL)
			zil_commit(zfsvfs->z_log, 0);

		ZFS_EXIT(zfsvfs);
	} else {
		/*
		 * Sync all ZFS filesystems.  This is what happens when you
		 * run sync(1M).  Unlike other filesystems, ZFS honors the
		 * request by waiting for all pools to commit all dirty data.
		 */
		spa_sync_allpools();
	}

	return (0);
}