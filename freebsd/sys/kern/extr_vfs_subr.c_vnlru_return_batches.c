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
struct vfsops {int dummy; } ;
struct mount {scalar_t__ mnt_tmpfreevnodelistsize; struct vfsops* mnt_op; } ;

/* Variables and functions */
 int MBF_MNTLSTLOCK ; 
 int MBF_NOWAIT ; 
 struct mount* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct mount* TAILQ_NEXT (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  mountlist ; 
 int /*<<< orphan*/  mountlist_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vfs_busy (struct mount*,int) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vnlru_return_batch (struct mount*) ; 

__attribute__((used)) static void
vnlru_return_batches(struct vfsops *mnt_op)
{
	struct mount *mp, *nmp;
	bool need_unbusy;

	mtx_lock(&mountlist_mtx);
	for (mp = TAILQ_FIRST(&mountlist); mp != NULL; mp = nmp) {
		need_unbusy = false;
		if (mnt_op != NULL && mp->mnt_op != mnt_op)
			goto next;
		if (mp->mnt_tmpfreevnodelistsize == 0)
			goto next;
		if (vfs_busy(mp, MBF_NOWAIT | MBF_MNTLSTLOCK) == 0) {
			vnlru_return_batch(mp);
			need_unbusy = true;
			mtx_lock(&mountlist_mtx);
		}
next:
		nmp = TAILQ_NEXT(mp, mnt_list);
		if (need_unbusy)
			vfs_unbusy(mp);
	}
	mtx_unlock(&mountlist_mtx);
}