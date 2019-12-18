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
struct ufsmount {struct fs* um_fs; } ;
struct mount {int mnt_kern_flag; } ;
struct fs {int /*<<< orphan*/  fs_fsmnt; } ;

/* Variables and functions */
 int FFSR_FORCE ; 
 int FFSR_UNSUSPEND ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MNTK_SUSPEND ; 
 struct ufsmount* VFSTOUFS (struct mount*) ; 
 int /*<<< orphan*/  curthread ; 
 int ffs_reload (struct mount*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffs_susp_lock ; 
 scalar_t__ ffs_susp_suspended (struct mount*) ; 
 int /*<<< orphan*/  ffs_susp_unsuspend (struct mount*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ffs_susp_dtor(void *data)
{
	struct fs *fs;
	struct ufsmount *ump;
	struct mount *mp;
	int error;

	sx_xlock(&ffs_susp_lock);

	mp = (struct mount *)data;
	ump = VFSTOUFS(mp);
	fs = ump->um_fs;

	if (ffs_susp_suspended(mp) == 0) {
		sx_xunlock(&ffs_susp_lock);
		return;
	}

	KASSERT((mp->mnt_kern_flag & MNTK_SUSPEND) != 0,
	    ("MNTK_SUSPEND not set"));

	error = ffs_reload(mp, curthread, FFSR_FORCE | FFSR_UNSUSPEND);
	if (error != 0)
		panic("failed to unsuspend writes on %s", fs->fs_fsmnt);

	ffs_susp_unsuspend(mp);
	sx_xunlock(&ffs_susp_lock);
}