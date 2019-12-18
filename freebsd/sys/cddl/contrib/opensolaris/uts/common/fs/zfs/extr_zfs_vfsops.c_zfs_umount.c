#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_2__* z_ctldir; TYPE_5__* z_os; int /*<<< orphan*/  z_unlinked_drain_task; int /*<<< orphan*/  z_teardown_lock; int /*<<< orphan*/  z_unmounted; TYPE_1__* z_parent; } ;
typedef  TYPE_3__ zfsvfs_t ;
struct TYPE_23__ {int vfs_count; int /*<<< orphan*/  vfs_resource; TYPE_3__* vfs_data; } ;
typedef  TYPE_4__ vfs_t ;
struct TYPE_24__ {int /*<<< orphan*/  os_user_ptr_lock; } ;
typedef  TYPE_5__ objset_t ;
struct TYPE_25__ {int /*<<< orphan*/ * td_ucred; } ;
typedef  TYPE_6__ kthread_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_26__ {int /*<<< orphan*/  tq_queue; } ;
struct TYPE_21__ {int v_count; } ;
struct TYPE_20__ {int /*<<< orphan*/  z_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  FORCECLOSE ; 
 int /*<<< orphan*/  FTAG ; 
 int MS_FORCE ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_MOUNT ; 
 TYPE_6__* curthread ; 
 int /*<<< orphan*/  dmu_objset_disown (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dmu_objset_set_user (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnlc_purge_vfsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_deleg_access (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ refstr_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrm_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrm_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int secpolicy_fs_unmount (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ taskqueue_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vflush (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  zfs_freevfs (TYPE_4__*) ; 
 int /*<<< orphan*/  zfsctl_destroy (TYPE_3__*) ; 
 int zfsctl_umount_snapshots (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 TYPE_8__* zfsvfs_taskq ; 
 scalar_t__ zfsvfs_teardown (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_umount(vfs_t *vfsp, int fflag)
{
	kthread_t *td = curthread;
	zfsvfs_t *zfsvfs = vfsp->vfs_data;
	objset_t *os;
	cred_t *cr = td->td_ucred;
	int ret;

	ret = secpolicy_fs_unmount(cr, vfsp);
	if (ret) {
		if (dsl_deleg_access((char *)refstr_value(vfsp->vfs_resource),
		    ZFS_DELEG_PERM_MOUNT, cr))
			return (ret);
	}

	/*
	 * We purge the parent filesystem's vfsp as the parent filesystem
	 * and all of its snapshots have their vnode's v_vfsp set to the
	 * parent's filesystem's vfsp.  Note, 'z_parent' is self
	 * referential for non-snapshots.
	 */
	(void) dnlc_purge_vfsp(zfsvfs->z_parent->z_vfs, 0);

	/*
	 * Unmount any snapshots mounted under .zfs before unmounting the
	 * dataset itself.
	 */
	if (zfsvfs->z_ctldir != NULL) {
		if ((ret = zfsctl_umount_snapshots(vfsp, fflag, cr)) != 0)
			return (ret);
	}

	if (fflag & MS_FORCE) {
		/*
		 * Mark file system as unmounted before calling
		 * vflush(FORCECLOSE). This way we ensure no future vnops
		 * will be called and risk operating on DOOMED vnodes.
		 */
		rrm_enter(&zfsvfs->z_teardown_lock, RW_WRITER, FTAG);
		zfsvfs->z_unmounted = B_TRUE;
		rrm_exit(&zfsvfs->z_teardown_lock, FTAG);
	}

	/*
	 * Flush all the files.
	 */
	ret = vflush(vfsp, 0, (fflag & MS_FORCE) ? FORCECLOSE : 0, td);
	if (ret != 0)
		return (ret);

#ifdef illumos
	if (!(fflag & MS_FORCE)) {
		/*
		 * Check the number of active vnodes in the file system.
		 * Our count is maintained in the vfs structure, but the
		 * number is off by 1 to indicate a hold on the vfs
		 * structure itself.
		 *
		 * The '.zfs' directory maintains a reference of its
		 * own, and any active references underneath are
		 * reflected in the vnode count.
		 */
		if (zfsvfs->z_ctldir == NULL) {
			if (vfsp->vfs_count > 1)
				return (SET_ERROR(EBUSY));
		} else {
			if (vfsp->vfs_count > 2 ||
			    zfsvfs->z_ctldir->v_count > 1)
				return (SET_ERROR(EBUSY));
		}
	}
#endif

	while (taskqueue_cancel(zfsvfs_taskq->tq_queue,
	    &zfsvfs->z_unlinked_drain_task, NULL) != 0)
		taskqueue_drain(zfsvfs_taskq->tq_queue,
		    &zfsvfs->z_unlinked_drain_task);

	VERIFY(zfsvfs_teardown(zfsvfs, B_TRUE) == 0);
	os = zfsvfs->z_os;

	/*
	 * z_os will be NULL if there was an error in
	 * attempting to reopen zfsvfs.
	 */
	if (os != NULL) {
		/*
		 * Unset the objset user_ptr.
		 */
		mutex_enter(&os->os_user_ptr_lock);
		dmu_objset_set_user(os, NULL);
		mutex_exit(&os->os_user_ptr_lock);

		/*
		 * Finally release the objset
		 */
		dmu_objset_disown(os, zfsvfs);
	}

	/*
	 * We can now safely destroy the '.zfs' directory node.
	 */
	if (zfsvfs->z_ctldir != NULL)
		zfsctl_destroy(zfsvfs);
	zfs_freevfs(vfsp);

	return (0);
}