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
struct vop_vptocnp_args {int /*<<< orphan*/  a_buflen; int /*<<< orphan*/  a_buf; struct ucred* a_cred; struct vnode** a_vpp; struct vnode* a_vp; } ;
struct vnode {struct mount* v_mount; } ;
struct ucred {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 struct vnode* NULLVPTOLOWERVP (struct vnode*) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int null_nodeget (struct mount*,struct vnode*,struct vnode**) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vfs_ref (struct mount*) ; 
 int /*<<< orphan*/  vfs_rel (struct mount*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int vn_lock (struct vnode*,int) ; 
 int vn_vptocnp (struct vnode**,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
null_vptocnp(struct vop_vptocnp_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode **dvp = ap->a_vpp;
	struct vnode *lvp, *ldvp;
	struct ucred *cred = ap->a_cred;
	struct mount *mp;
	int error, locked;

	locked = VOP_ISLOCKED(vp);
	lvp = NULLVPTOLOWERVP(vp);
	vhold(lvp);
	mp = vp->v_mount;
	vfs_ref(mp);
	VOP_UNLOCK(vp, 0); /* vp is held by vn_vptocnp_locked that called us */
	ldvp = lvp;
	vref(lvp);
	error = vn_vptocnp(&ldvp, cred, ap->a_buf, ap->a_buflen);
	vdrop(lvp);
	if (error != 0) {
		vn_lock(vp, locked | LK_RETRY);
		vfs_rel(mp);
		return (ENOENT);
	}

	error = vn_lock(ldvp, LK_SHARED);
	if (error != 0) {
		vrele(ldvp);
		vn_lock(vp, locked | LK_RETRY);
		vfs_rel(mp);
		return (ENOENT);
	}
	error = null_nodeget(mp, ldvp, dvp);
	if (error == 0) {
#ifdef DIAGNOSTIC
		NULLVPTOLOWERVP(*dvp);
#endif
		VOP_UNLOCK(*dvp, 0); /* keep reference on *dvp */
	}
	vn_lock(vp, locked | LK_RETRY);
	vfs_rel(mp);
	return (error);
}