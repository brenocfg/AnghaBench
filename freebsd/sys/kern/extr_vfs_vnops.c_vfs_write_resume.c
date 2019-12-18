#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mount {int mnt_kern_flag; int /*<<< orphan*/  mnt_writeopcount; int /*<<< orphan*/  mnt_flag; TYPE_1__* mnt_susp_owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_pflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MNTK_SUSPEND ; 
 int MNTK_SUSPEND2 ; 
 int MNTK_SUSPENDED ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_REF (struct mount*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDP_IGNSUSP ; 
 int /*<<< orphan*/  VFS_SUSP_CLEAN (struct mount*) ; 
 int VR_NO_SUSPCLR ; 
 int VR_START_WRITE ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  vfs_op_exit (struct mount*) ; 
 int /*<<< orphan*/  vn_start_write_refed (struct mount*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vn_suspendable (struct mount*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
vfs_write_resume(struct mount *mp, int flags)
{

	MPASS(vn_suspendable(mp));

	MNT_ILOCK(mp);
	if ((mp->mnt_kern_flag & MNTK_SUSPEND) != 0) {
		KASSERT(mp->mnt_susp_owner == curthread, ("mnt_susp_owner"));
		mp->mnt_kern_flag &= ~(MNTK_SUSPEND | MNTK_SUSPEND2 |
				       MNTK_SUSPENDED);
		mp->mnt_susp_owner = NULL;
		wakeup(&mp->mnt_writeopcount);
		wakeup(&mp->mnt_flag);
		curthread->td_pflags &= ~TDP_IGNSUSP;
		if ((flags & VR_START_WRITE) != 0) {
			MNT_REF(mp);
			mp->mnt_writeopcount++;
		}
		MNT_IUNLOCK(mp);
		if ((flags & VR_NO_SUSPCLR) == 0)
			VFS_SUSP_CLEAN(mp);
		vfs_op_exit(mp);
	} else if ((flags & VR_START_WRITE) != 0) {
		MNT_REF(mp);
		vn_start_write_refed(mp, 0, true);
	} else {
		MNT_IUNLOCK(mp);
	}
}