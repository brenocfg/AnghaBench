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
struct mount {int mnt_kern_flag; int /*<<< orphan*/  mnt_flag; } ;
struct TYPE_2__ {int td_pflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MNTK_SUSPEND2 ; 
 int MNTK_SUSPENDED ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int TDP_IGNSUSP ; 
 int /*<<< orphan*/  V_WAIT ; 
 TYPE_1__* curthread ; 
 int vfs_write_suspend (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_start_write (int /*<<< orphan*/ *,struct mount**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_suspendable (struct mount*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
vfs_write_suspend_umnt(struct mount *mp)
{
	int error;

	MPASS(vn_suspendable(mp));
	KASSERT((curthread->td_pflags & TDP_IGNSUSP) == 0,
	    ("vfs_write_suspend_umnt: recursed"));

	/* dounmount() already called vn_start_write(). */
	for (;;) {
		vn_finished_write(mp);
		error = vfs_write_suspend(mp, 0);
		if (error != 0) {
			vn_start_write(NULL, &mp, V_WAIT);
			return (error);
		}
		MNT_ILOCK(mp);
		if ((mp->mnt_kern_flag & MNTK_SUSPENDED) != 0)
			break;
		MNT_IUNLOCK(mp);
		vn_start_write(NULL, &mp, V_WAIT);
	}
	mp->mnt_kern_flag &= ~(MNTK_SUSPENDED | MNTK_SUSPEND2);
	wakeup(&mp->mnt_flag);
	MNT_IUNLOCK(mp);
	curthread->td_pflags |= TDP_IGNSUSP;
	return (0);
}