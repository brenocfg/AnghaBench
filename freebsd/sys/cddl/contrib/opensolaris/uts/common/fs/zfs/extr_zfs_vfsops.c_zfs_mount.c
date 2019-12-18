#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ z_issnap; int /*<<< orphan*/  z_teardown_lock; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct TYPE_29__ {scalar_t__ v_type; int v_count; int v_flag; int /*<<< orphan*/  v_vfsp; int /*<<< orphan*/  v_lock; } ;
typedef  TYPE_2__ vnode_t ;
struct TYPE_30__ {int vfs_flag; TYPE_1__* vfs_data; int /*<<< orphan*/  mnt_optnew; TYPE_2__* mnt_vnodecovered; } ;
typedef  TYPE_3__ vfs_t ;
struct TYPE_31__ {int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_mask; } ;
typedef  TYPE_4__ vattr_t ;
struct TYPE_32__ {int /*<<< orphan*/ * td_ucred; } ;
typedef  TYPE_5__ kthread_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_27__ {char* pn_path; } ;
struct TYPE_26__ {int flags; scalar_t__ datalen; int /*<<< orphan*/  spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_UID ; 
 int /*<<< orphan*/  DROP_GIANT () ; 
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ ECANCELED ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  INGLOBALZONE (TYPE_5__*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int MAXNAMELEN ; 
 int MNT_NFS4ACLS ; 
 int MNT_ROOTFS ; 
 int MNT_UPDATE ; 
 int MS_DATA ; 
 int MS_OVERLAY ; 
 int MS_REMOUNT ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VFS_HOLD (int /*<<< orphan*/ ) ; 
 scalar_t__ VOP_ACCESS (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ VOP_GETATTR (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int VROOT ; 
 int /*<<< orphan*/  VWRITE ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_MOUNT ; 
 TYPE_5__* curthread ; 
 scalar_t__ dsl_deleg_access (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fromspace ; 
 int getpoolname (char*,char*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int pn_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*) ; 
 int /*<<< orphan*/  rrm_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrm_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int secpolicy_fs_mount (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  secpolicy_fs_mount_clearopts (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ secpolicy_vnode_owner (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_import_rootpool (char*) ; 
 TYPE_13__ spn ; 
 TYPE_12__* uap ; 
 scalar_t__ vfs_getopt (int /*<<< orphan*/ ,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (TYPE_2__*,int) ; 
 int zfs_domount (TYPE_3__*,char*) ; 
 int zfs_mount_label_policy (TYPE_3__*,char*) ; 
 int zfs_register_callbacks (TYPE_3__*) ; 
 scalar_t__ zfs_super_owner ; 
 int /*<<< orphan*/  zfs_unregister_callbacks (TYPE_1__*) ; 
 int /*<<< orphan*/  zone_dataset_visible (char*,int*) ; 

__attribute__((used)) static int
zfs_mount(vfs_t *vfsp)
{
	kthread_t	*td = curthread;
	vnode_t		*mvp = vfsp->mnt_vnodecovered;
	cred_t		*cr = td->td_ucred;
	char		*osname;
	int		error = 0;
	int		canwrite;

#ifdef illumos
	if (mvp->v_type != VDIR)
		return (SET_ERROR(ENOTDIR));

	mutex_enter(&mvp->v_lock);
	if ((uap->flags & MS_REMOUNT) == 0 &&
	    (uap->flags & MS_OVERLAY) == 0 &&
	    (mvp->v_count != 1 || (mvp->v_flag & VROOT))) {
		mutex_exit(&mvp->v_lock);
		return (SET_ERROR(EBUSY));
	}
	mutex_exit(&mvp->v_lock);

	/*
	 * ZFS does not support passing unparsed data in via MS_DATA.
	 * Users should use the MS_OPTIONSTR interface; this means
	 * that all option parsing is already done and the options struct
	 * can be interrogated.
	 */
	if ((uap->flags & MS_DATA) && uap->datalen > 0)
		return (SET_ERROR(EINVAL));

	/*
	 * Get the objset name (the "special" mount argument).
	 */
	if (error = pn_get(uap->spec, fromspace, &spn))
		return (error);

	osname = spn.pn_path;
#else	/* !illumos */
	if (vfs_getopt(vfsp->mnt_optnew, "from", (void **)&osname, NULL))
		return (SET_ERROR(EINVAL));

	/*
	 * If full-owner-access is enabled and delegated administration is
	 * turned on, we must set nosuid.
	 */
	if (zfs_super_owner &&
	    dsl_deleg_access(osname, ZFS_DELEG_PERM_MOUNT, cr) != ECANCELED) {
		secpolicy_fs_mount_clearopts(cr, vfsp);
	}
#endif	/* illumos */

	/*
	 * Check for mount privilege?
	 *
	 * If we don't have privilege then see if
	 * we have local permission to allow it
	 */
	error = secpolicy_fs_mount(cr, mvp, vfsp);
	if (error) {
		if (dsl_deleg_access(osname, ZFS_DELEG_PERM_MOUNT, cr) != 0)
			goto out;

		if (!(vfsp->vfs_flag & MS_REMOUNT)) {
			vattr_t		vattr;

			/*
			 * Make sure user is the owner of the mount point
			 * or has sufficient privileges.
			 */

			vattr.va_mask = AT_UID;

			vn_lock(mvp, LK_SHARED | LK_RETRY);
			if (VOP_GETATTR(mvp, &vattr, cr)) {
				VOP_UNLOCK(mvp, 0);
				goto out;
			}

			if (secpolicy_vnode_owner(mvp, cr, vattr.va_uid) != 0 &&
			    VOP_ACCESS(mvp, VWRITE, cr, td) != 0) {
				VOP_UNLOCK(mvp, 0);
				goto out;
			}
			VOP_UNLOCK(mvp, 0);
		}

		secpolicy_fs_mount_clearopts(cr, vfsp);
	}

	/*
	 * Refuse to mount a filesystem if we are in a local zone and the
	 * dataset is not visible.
	 */
	if (!INGLOBALZONE(curthread) &&
	    (!zone_dataset_visible(osname, &canwrite) || !canwrite)) {
		error = SET_ERROR(EPERM);
		goto out;
	}

#ifdef SECLABEL
	error = zfs_mount_label_policy(vfsp, osname);
	if (error)
		goto out;
#endif

	vfsp->vfs_flag |= MNT_NFS4ACLS;

	/*
	 * When doing a remount, we simply refresh our temporary properties
	 * according to those options set in the current VFS options.
	 */
	if (vfsp->vfs_flag & MS_REMOUNT) {
		zfsvfs_t *zfsvfs = vfsp->vfs_data;

		/*
		 * Refresh mount options with z_teardown_lock blocking I/O while
		 * the filesystem is in an inconsistent state.
		 * The lock also serializes this code with filesystem
		 * manipulations between entry to zfs_suspend_fs() and return
		 * from zfs_resume_fs().
		 */
		rrm_enter(&zfsvfs->z_teardown_lock, RW_WRITER, FTAG);
		zfs_unregister_callbacks(zfsvfs);
		error = zfs_register_callbacks(vfsp);
		rrm_exit(&zfsvfs->z_teardown_lock, FTAG);
		goto out;
	}

	/* Initial root mount: try hard to import the requested root pool. */
	if ((vfsp->vfs_flag & MNT_ROOTFS) != 0 &&
	    (vfsp->vfs_flag & MNT_UPDATE) == 0) {
		char pname[MAXNAMELEN];

		error = getpoolname(osname, pname);
		if (error == 0)
			error = spa_import_rootpool(pname);
		if (error)
			goto out;
	}
	DROP_GIANT();
	error = zfs_domount(vfsp, osname);
	PICKUP_GIANT();

#ifdef illumos
	/*
	 * Add an extra VFS_HOLD on our parent vfs so that it can't
	 * disappear due to a forced unmount.
	 */
	if (error == 0 && ((zfsvfs_t *)vfsp->vfs_data)->z_issnap)
		VFS_HOLD(mvp->v_vfsp);
#endif

out:
	return (error);
}