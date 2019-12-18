#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ufsmount {int /*<<< orphan*/  um_flags; int /*<<< orphan*/  um_devvp; } ;
struct mount {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  UFS_LOCK (struct ufsmount*) ; 
 int /*<<< orphan*/  UFS_UNLOCK (struct ufsmount*) ; 
 int /*<<< orphan*/  UM_WRITESUSPENDED ; 
 struct ufsmount* VFSTOUFS (struct mount*) ; 
 int VOP_ACCESS (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VREAD ; 
 int /*<<< orphan*/  VS_SKIP_UNMOUNT ; 
 int VWRITE ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  ffs_own_mount (struct mount*) ; 
 int /*<<< orphan*/  ffs_susp_lock ; 
 scalar_t__ ffs_susp_suspended (struct mount*) ; 
 scalar_t__ mac_mount_check_stat (int /*<<< orphan*/ ,struct mount*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vfs_write_suspend (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ffs_susp_suspend(struct mount *mp)
{
	struct ufsmount *ump;
	int error;

	sx_assert(&ffs_susp_lock, SA_XLOCKED);

	if (!ffs_own_mount(mp))
		return (EINVAL);
	if (ffs_susp_suspended(mp))
		return (EBUSY);

	ump = VFSTOUFS(mp);

	/*
	 * Make sure the calling thread is permitted to access the mounted
	 * device.  The permissions can change after we unlock the vnode;
	 * it's harmless.
	 */
	vn_lock(ump->um_devvp, LK_EXCLUSIVE | LK_RETRY);
	error = VOP_ACCESS(ump->um_devvp, VREAD | VWRITE,
	    curthread->td_ucred, curthread);
	VOP_UNLOCK(ump->um_devvp, 0);
	if (error != 0)
		return (error);
#ifdef MAC
	if (mac_mount_check_stat(curthread->td_ucred, mp) != 0)
		return (EPERM);
#endif

	if ((error = vfs_write_suspend(mp, VS_SKIP_UNMOUNT)) != 0)
		return (error);

	UFS_LOCK(ump);
	ump->um_flags |= UM_WRITESUSPENDED;
	UFS_UNLOCK(ump);

	return (0);
}