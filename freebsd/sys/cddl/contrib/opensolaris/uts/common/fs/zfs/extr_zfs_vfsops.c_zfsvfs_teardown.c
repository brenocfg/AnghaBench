#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ z_sa_hdl; } ;
typedef  TYPE_3__ znode_t ;
struct TYPE_17__ {int /*<<< orphan*/ * z_os; TYPE_2__* z_vfs; int /*<<< orphan*/  z_teardown_lock; int /*<<< orphan*/  z_teardown_inactive_lock; scalar_t__ z_unmounted; int /*<<< orphan*/  z_znodes_lock; int /*<<< orphan*/  z_all_znodes; int /*<<< orphan*/ * z_log; TYPE_1__* z_parent; } ;
typedef  TYPE_4__ zfsvfs_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_15__ {int vfs_flag; } ;
struct TYPE_14__ {int /*<<< orphan*/  z_vfs; } ;
struct TYPE_13__ {scalar_t__ v_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int VFS_RDONLY ; 
 TYPE_11__* ZTOV (TYPE_3__*) ; 
 int /*<<< orphan*/  cache_purgevfs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_evict_dbufs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnlc_purge_vfsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_dataset_is_dirty (int /*<<< orphan*/ ) ; 
 TYPE_3__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_3__* list_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrm_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrm_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_unregister_callbacks (TYPE_4__*) ; 
 int /*<<< orphan*/  zfs_znode_dmu_fini (TYPE_3__*) ; 
 int /*<<< orphan*/  zil_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfsvfs_teardown(zfsvfs_t *zfsvfs, boolean_t unmounting)
{
	znode_t	*zp;

	rrm_enter(&zfsvfs->z_teardown_lock, RW_WRITER, FTAG);

	if (!unmounting) {
		/*
		 * We purge the parent filesystem's vfsp as the parent
		 * filesystem and all of its snapshots have their vnode's
		 * v_vfsp set to the parent's filesystem's vfsp.  Note,
		 * 'z_parent' is self referential for non-snapshots.
		 */
		(void) dnlc_purge_vfsp(zfsvfs->z_parent->z_vfs, 0);
#ifdef FREEBSD_NAMECACHE
		cache_purgevfs(zfsvfs->z_parent->z_vfs, true);
#endif
	}

	/*
	 * Close the zil. NB: Can't close the zil while zfs_inactive
	 * threads are blocked as zil_close can call zfs_inactive.
	 */
	if (zfsvfs->z_log) {
		zil_close(zfsvfs->z_log);
		zfsvfs->z_log = NULL;
	}

	rw_enter(&zfsvfs->z_teardown_inactive_lock, RW_WRITER);

	/*
	 * If we are not unmounting (ie: online recv) and someone already
	 * unmounted this file system while we were doing the switcheroo,
	 * or a reopen of z_os failed then just bail out now.
	 */
	if (!unmounting && (zfsvfs->z_unmounted || zfsvfs->z_os == NULL)) {
		rw_exit(&zfsvfs->z_teardown_inactive_lock);
		rrm_exit(&zfsvfs->z_teardown_lock, FTAG);
		return (SET_ERROR(EIO));
	}

	/*
	 * At this point there are no vops active, and any new vops will
	 * fail with EIO since we have z_teardown_lock for writer (only
	 * relavent for forced unmount).
	 *
	 * Release all holds on dbufs.
	 */
	mutex_enter(&zfsvfs->z_znodes_lock);
	for (zp = list_head(&zfsvfs->z_all_znodes); zp != NULL;
	    zp = list_next(&zfsvfs->z_all_znodes, zp))
		if (zp->z_sa_hdl) {
			ASSERT(ZTOV(zp)->v_count >= 0);
			zfs_znode_dmu_fini(zp);
		}
	mutex_exit(&zfsvfs->z_znodes_lock);

	/*
	 * If we are unmounting, set the unmounted flag and let new vops
	 * unblock.  zfs_inactive will have the unmounted behavior, and all
	 * other vops will fail with EIO.
	 */
	if (unmounting) {
		zfsvfs->z_unmounted = B_TRUE;
		rw_exit(&zfsvfs->z_teardown_inactive_lock);
		rrm_exit(&zfsvfs->z_teardown_lock, FTAG);
	}

	/*
	 * z_os will be NULL if there was an error in attempting to reopen
	 * zfsvfs, so just return as the properties had already been
	 * unregistered and cached data had been evicted before.
	 */
	if (zfsvfs->z_os == NULL)
		return (0);

	/*
	 * Unregister properties.
	 */
	zfs_unregister_callbacks(zfsvfs);

	/*
	 * Evict cached data
	 */
	if (dsl_dataset_is_dirty(dmu_objset_ds(zfsvfs->z_os)) &&
	    !(zfsvfs->z_vfs->vfs_flag & VFS_RDONLY))
		txg_wait_synced(dmu_objset_pool(zfsvfs->z_os), 0);
	dmu_objset_evict_dbufs(zfsvfs->z_os);

	return (0);
}