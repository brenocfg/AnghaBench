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
struct vnode {int dummy; } ;
struct mount {int mnt_kern_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MNTK_MWAIT ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_MTX (struct mount*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vfs_op_exit_locked (struct mount*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  wakeup (struct mount*) ; 

__attribute__((used)) static void
dounmount_cleanup(struct mount *mp, struct vnode *coveredvp, int mntkflags)
{

	mtx_assert(MNT_MTX(mp), MA_OWNED);
	mp->mnt_kern_flag &= ~mntkflags;
	if ((mp->mnt_kern_flag & MNTK_MWAIT) != 0) {
		mp->mnt_kern_flag &= ~MNTK_MWAIT;
		wakeup(mp);
	}
	vfs_op_exit_locked(mp);
	MNT_IUNLOCK(mp);
	if (coveredvp != NULL) {
		VOP_UNLOCK(coveredvp, 0);
		vdrop(coveredvp);
	}
	vn_finished_write(mp);
}