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
typedef  int (* vn_get_ino_t ) (struct mount*,void*,int,struct vnode**) ;
struct vnode {int v_iflag; struct mount* v_mount; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  MBF_NOWAIT ; 
 int VI_DOOMED ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_ref (struct mount*) ; 
 int /*<<< orphan*/  vfs_rel (struct mount*) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vunref (struct vnode*) ; 

int
vn_vget_ino_gen(struct vnode *vp, vn_get_ino_t alloc, void *alloc_arg,
    int lkflags, struct vnode **rvp)
{
	struct mount *mp;
	int ltype, error;

	ASSERT_VOP_LOCKED(vp, "vn_vget_ino_get");
	mp = vp->v_mount;
	ltype = VOP_ISLOCKED(vp);
	KASSERT(ltype == LK_EXCLUSIVE || ltype == LK_SHARED,
	    ("vn_vget_ino: vp not locked"));
	error = vfs_busy(mp, MBF_NOWAIT);
	if (error != 0) {
		vfs_ref(mp);
		VOP_UNLOCK(vp, 0);
		error = vfs_busy(mp, 0);
		vn_lock(vp, ltype | LK_RETRY);
		vfs_rel(mp);
		if (error != 0)
			return (ENOENT);
		if (vp->v_iflag & VI_DOOMED) {
			vfs_unbusy(mp);
			return (ENOENT);
		}
	}
	VOP_UNLOCK(vp, 0);
	error = alloc(mp, alloc_arg, lkflags, rvp);
	vfs_unbusy(mp);
	if (error != 0 || *rvp != vp)
		vn_lock(vp, ltype | LK_RETRY);
	if (vp->v_iflag & VI_DOOMED) {
		if (error == 0) {
			if (*rvp == vp)
				vunref(vp);
			else
				vput(*rvp);
		}
		error = ENOENT;
	}
	return (error);
}