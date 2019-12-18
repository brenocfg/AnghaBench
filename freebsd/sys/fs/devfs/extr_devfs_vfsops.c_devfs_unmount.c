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
typedef  int /*<<< orphan*/  u_int ;
struct mount {int /*<<< orphan*/ * mnt_data; } ;
struct devfs_mount {int dm_holdcnt; int /*<<< orphan*/  dm_lock; int /*<<< orphan*/  dm_idx; int /*<<< orphan*/ * dm_mount; } ;

/* Variables and functions */
 int FORCECLOSE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int MNT_FORCE ; 
 struct devfs_mount* VFSTODEVFS (struct mount*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  devfs_cleanup (struct devfs_mount*) ; 
 int /*<<< orphan*/  devfs_rules_cleanup (struct devfs_mount*) ; 
 int /*<<< orphan*/  devfs_unmount_final (struct devfs_mount*) ; 
 int /*<<< orphan*/  devfs_unr ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int vflush (struct mount*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devfs_unmount(struct mount *mp, int mntflags)
{
	int error;
	int flags = 0;
	struct devfs_mount *fmp;
	int hold;
	u_int idx;

	fmp = VFSTODEVFS(mp);
	KASSERT(fmp->dm_mount != NULL,
		("devfs_unmount unmounted devfs_mount"));
	if (mntflags & MNT_FORCE)
		flags |= FORCECLOSE;
	/* There is 1 extra root vnode reference from devfs_mount(). */
	error = vflush(mp, 1, flags, curthread);
	if (error)
		return (error);
	sx_xlock(&fmp->dm_lock);
	devfs_cleanup(fmp);
	devfs_rules_cleanup(fmp);
	fmp->dm_mount = NULL;
	hold = --fmp->dm_holdcnt;
	mp->mnt_data = NULL;
	idx = fmp->dm_idx;
	sx_xunlock(&fmp->dm_lock);
	free_unr(devfs_unr, idx);
	if (hold == 0)
		devfs_unmount_final(fmp);
	return 0;
}