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
struct ufsmount {int /*<<< orphan*/  um_flags; } ;
struct mount {int /*<<< orphan*/  mnt_susp_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  UFS_LOCK (struct ufsmount*) ; 
 int /*<<< orphan*/  UFS_UNLOCK (struct ufsmount*) ; 
 int /*<<< orphan*/  UM_WRITESUSPENDED ; 
 struct ufsmount* VFSTOUFS (struct mount*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  ffs_susp_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vfs_write_resume (struct mount*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ffs_susp_unsuspend(struct mount *mp)
{
	struct ufsmount *ump;

	sx_assert(&ffs_susp_lock, SA_XLOCKED);

	/*
	 * XXX: The status is kept per-process; the vfs_write_resume() routine
	 * 	asserts that the resuming thread is the same one that called
	 * 	vfs_write_suspend().  The cdevpriv data, however, is attached
	 * 	to the file descriptor, e.g. is inherited during fork.  Thus,
	 * 	it's possible that the resuming process will be different from
	 * 	the one that started the suspension.
	 *
	 * 	Work around by fooling the check in vfs_write_resume().
	 */
	mp->mnt_susp_owner = curthread;

	vfs_write_resume(mp, 0);
	ump = VFSTOUFS(mp);
	UFS_LOCK(ump);
	ump->um_flags &= ~UM_WRITESUSPENDED;
	UFS_UNLOCK(ump);
	vfs_unbusy(mp);
}