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
struct TYPE_5__ {int /*<<< orphan*/ * z_hold_mtx; int /*<<< orphan*/  z_fuid_lock; int /*<<< orphan*/  z_teardown_inactive_lock; int /*<<< orphan*/  z_teardown_lock; int /*<<< orphan*/  z_all_znodes; int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_znodes_lock; } ;
typedef  TYPE_1__ zfsvfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 int ZFS_OBJ_MTX_SZ ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_fuid_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  zfsvfs_lock ; 

void
zfsvfs_free(zfsvfs_t *zfsvfs)
{
	int i;

	/*
	 * This is a barrier to prevent the filesystem from going away in
	 * zfs_znode_move() until we can safely ensure that the filesystem is
	 * not unmounted. We consider the filesystem valid before the barrier
	 * and invalid after the barrier.
	 */
	rw_enter(&zfsvfs_lock, RW_READER);
	rw_exit(&zfsvfs_lock);

	zfs_fuid_destroy(zfsvfs);

	mutex_destroy(&zfsvfs->z_znodes_lock);
	mutex_destroy(&zfsvfs->z_lock);
	list_destroy(&zfsvfs->z_all_znodes);
	rrm_destroy(&zfsvfs->z_teardown_lock);
	rw_destroy(&zfsvfs->z_teardown_inactive_lock);
	rw_destroy(&zfsvfs->z_fuid_lock);
	for (i = 0; i != ZFS_OBJ_MTX_SZ; i++)
		mutex_destroy(&zfsvfs->z_hold_mtx[i]);
	kmem_free(zfsvfs, sizeof (zfsvfs_t));
}