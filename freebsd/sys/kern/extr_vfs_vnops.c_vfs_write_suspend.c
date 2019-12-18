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
struct mount {scalar_t__ mnt_susp_owner; int mnt_kern_flag; scalar_t__ mnt_flag; scalar_t__ mnt_writeopcount; } ;

/* Variables and functions */
 int EALREADY ; 
 int EBUSY ; 
 int MNTK_SUSPEND ; 
 int MNTK_UNMOUNT ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_MTX (struct mount*) ; 
 int /*<<< orphan*/  MNT_SUSPEND ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int PDROP ; 
 int PUSER ; 
 int VFS_SYNC (struct mount*,int /*<<< orphan*/ ) ; 
 int VS_SKIP_UNMOUNT ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_assert_mount_counters (struct mount*) ; 
 int /*<<< orphan*/  vfs_op_enter (struct mount*) ; 
 int /*<<< orphan*/  vfs_op_exit (struct mount*) ; 
 int /*<<< orphan*/  vfs_op_exit_locked (struct mount*) ; 
 int /*<<< orphan*/  vfs_write_resume (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_suspendable (struct mount*) ; 

int
vfs_write_suspend(struct mount *mp, int flags)
{
	int error;

	MPASS(vn_suspendable(mp));

	vfs_op_enter(mp);

	MNT_ILOCK(mp);
	vfs_assert_mount_counters(mp);
	if (mp->mnt_susp_owner == curthread) {
		vfs_op_exit_locked(mp);
		MNT_IUNLOCK(mp);
		return (EALREADY);
	}
	while (mp->mnt_kern_flag & MNTK_SUSPEND)
		msleep(&mp->mnt_flag, MNT_MTX(mp), PUSER - 1, "wsuspfs", 0);

	/*
	 * Unmount holds a write reference on the mount point.  If we
	 * own busy reference and drain for writers, we deadlock with
	 * the reference draining in the unmount path.  Callers of
	 * vfs_write_suspend() must specify VS_SKIP_UNMOUNT if
	 * vfs_busy() reference is owned and caller is not in the
	 * unmount context.
	 */
	if ((flags & VS_SKIP_UNMOUNT) != 0 &&
	    (mp->mnt_kern_flag & MNTK_UNMOUNT) != 0) {
		vfs_op_exit_locked(mp);
		MNT_IUNLOCK(mp);
		return (EBUSY);
	}

	mp->mnt_kern_flag |= MNTK_SUSPEND;
	mp->mnt_susp_owner = curthread;
	if (mp->mnt_writeopcount > 0)
		(void) msleep(&mp->mnt_writeopcount, 
		    MNT_MTX(mp), (PUSER - 1)|PDROP, "suspwt", 0);
	else
		MNT_IUNLOCK(mp);
	if ((error = VFS_SYNC(mp, MNT_SUSPEND)) != 0) {
		vfs_write_resume(mp, 0);
		vfs_op_exit(mp);
	}
	return (error);
}