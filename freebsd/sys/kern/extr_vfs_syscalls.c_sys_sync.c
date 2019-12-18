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
struct thread {int dummy; } ;
struct sync_args {int dummy; } ;
struct mount {int mnt_flag; } ;

/* Variables and functions */
 int MBF_MNTLSTLOCK ; 
 int MBF_NOWAIT ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int MNT_RDONLY ; 
 struct mount* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct mount* TAILQ_NEXT (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDP_SYNCIO ; 
 int /*<<< orphan*/  VFS_SYNC (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_NOWAIT ; 
 int /*<<< orphan*/  curthread_pflags_restore (int) ; 
 int curthread_pflags_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  mountlist ; 
 int /*<<< orphan*/  mountlist_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vfs_busy (struct mount*,int) ; 
 int /*<<< orphan*/  vfs_msync (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 scalar_t__ vn_start_write (int /*<<< orphan*/ *,struct mount**,int /*<<< orphan*/ ) ; 

int
sys_sync(struct thread *td, struct sync_args *uap)
{
	struct mount *mp, *nmp;
	int save;

	mtx_lock(&mountlist_mtx);
	for (mp = TAILQ_FIRST(&mountlist); mp != NULL; mp = nmp) {
		if (vfs_busy(mp, MBF_NOWAIT | MBF_MNTLSTLOCK)) {
			nmp = TAILQ_NEXT(mp, mnt_list);
			continue;
		}
		if ((mp->mnt_flag & MNT_RDONLY) == 0 &&
		    vn_start_write(NULL, &mp, V_NOWAIT) == 0) {
			save = curthread_pflags_set(TDP_SYNCIO);
			vfs_msync(mp, MNT_NOWAIT);
			VFS_SYNC(mp, MNT_NOWAIT);
			curthread_pflags_restore(save);
			vn_finished_write(mp);
		}
		mtx_lock(&mountlist_mtx);
		nmp = TAILQ_NEXT(mp, mnt_list);
		vfs_unbusy(mp);
	}
	mtx_unlock(&mountlist_mtx);
	return (0);
}