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
struct mount {int mnt_flag; } ;
struct TYPE_2__ {int tm_ronly; } ;

/* Variables and functions */
 int EBUSY ; 
 int FORCECLOSE ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_RDONLY ; 
 TYPE_1__* VFS_TO_TMPFS (struct mount*) ; 
 int /*<<< orphan*/  V_WAIT ; 
 int WRITECLOSE ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  tmpfs_all_rw_maps (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tmpfs_check_rw_maps (struct mount*) ; 
 int /*<<< orphan*/  tmpfs_revoke_rw_maps_cb ; 
 int /*<<< orphan*/  tmpfs_update_mtime (struct mount*,int) ; 
 int vflush (struct mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_write_resume (struct mount*,int /*<<< orphan*/ ) ; 
 int vfs_write_suspend_umnt (struct mount*) ; 
 int vn_start_write (int /*<<< orphan*/ *,struct mount**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tmpfs_rw_to_ro(struct mount *mp)
{
	int error, flags;
	bool forced;

	forced = (mp->mnt_flag & MNT_FORCE) != 0;
	flags = WRITECLOSE | (forced ? FORCECLOSE : 0);

	if ((error = vn_start_write(NULL, &mp, V_WAIT)) != 0)
		return (error);
	error = vfs_write_suspend_umnt(mp);
	if (error != 0)
		return (error);
	if (!forced && tmpfs_check_rw_maps(mp)) {
		error = EBUSY;
		goto out;
	}
	VFS_TO_TMPFS(mp)->tm_ronly = 1;
	MNT_ILOCK(mp);
	mp->mnt_flag |= MNT_RDONLY;
	MNT_IUNLOCK(mp);
	for (;;) {
		tmpfs_all_rw_maps(mp, tmpfs_revoke_rw_maps_cb, NULL);
		tmpfs_update_mtime(mp, false);
		error = vflush(mp, 0, flags, curthread);
		if (error != 0) {
			VFS_TO_TMPFS(mp)->tm_ronly = 0;
			MNT_ILOCK(mp);
			mp->mnt_flag &= ~MNT_RDONLY;
			MNT_IUNLOCK(mp);
			goto out;
		}
		if (!tmpfs_check_rw_maps(mp))
			break;
	}
out:
	vfs_write_resume(mp, 0);
	return (error);
}