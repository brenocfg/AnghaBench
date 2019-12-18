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
struct vop_lookup_args {struct vnode** a_vpp; struct vnode* a_dvp; struct componentname* a_cnp; } ;
struct vnode {int v_vflag; int v_iflag; struct mount* v_mount; } ;
struct mount {int mnt_flag; } ;
struct componentname {int cn_flags; scalar_t__ cn_nameiop; } ;

/* Variables and functions */
 scalar_t__ CREATE ; 
 scalar_t__ DELETE ; 
 int EJUSTRETURN ; 
 int ENOENT ; 
 int EROFS ; 
 int ISDOTDOT ; 
 int ISLASTCN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int MNT_RDONLY ; 
 struct vnode* NULLVPTOLOWERVP (struct vnode*) ; 
 scalar_t__ RENAME ; 
 int VI_DOOMED ; 
 int VOP_LOOKUP (struct vnode*,struct vnode**,struct componentname*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VREF (struct vnode*) ; 
 int VV_ROOT ; 
 int null_nodeget (struct mount*,struct vnode*,struct vnode**) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
null_lookup(struct vop_lookup_args *ap)
{
	struct componentname *cnp = ap->a_cnp;
	struct vnode *dvp = ap->a_dvp;
	int flags = cnp->cn_flags;
	struct vnode *vp, *ldvp, *lvp;
	struct mount *mp;
	int error;

	mp = dvp->v_mount;
	if ((flags & ISLASTCN) != 0 && (mp->mnt_flag & MNT_RDONLY) != 0 &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME))
		return (EROFS);
	/*
	 * Although it is possible to call null_bypass(), we'll do
	 * a direct call to reduce overhead
	 */
	ldvp = NULLVPTOLOWERVP(dvp);
	vp = lvp = NULL;
	KASSERT((ldvp->v_vflag & VV_ROOT) == 0 ||
	    ((dvp->v_vflag & VV_ROOT) != 0 && (flags & ISDOTDOT) == 0),
	    ("ldvp %p fl %#x dvp %p fl %#x flags %#x", ldvp, ldvp->v_vflag,
	     dvp, dvp->v_vflag, flags));

	/*
	 * Hold ldvp.  The reference on it, owned by dvp, is lost in
	 * case of dvp reclamation, and we need ldvp to move our lock
	 * from ldvp to dvp.
	 */
	vhold(ldvp);

	error = VOP_LOOKUP(ldvp, &lvp, cnp);

	/*
	 * VOP_LOOKUP() on lower vnode may unlock ldvp, which allows
	 * dvp to be reclaimed due to shared v_vnlock.  Check for the
	 * doomed state and return error.
	 */
	if ((error == 0 || error == EJUSTRETURN) &&
	    (dvp->v_iflag & VI_DOOMED) != 0) {
		error = ENOENT;
		if (lvp != NULL)
			vput(lvp);

		/*
		 * If vgone() did reclaimed dvp before curthread
		 * relocked ldvp, the locks of dvp and ldpv are no
		 * longer shared.  In this case, relock of ldvp in
		 * lower fs VOP_LOOKUP() does not restore the locking
		 * state of dvp.  Compensate for this by unlocking
		 * ldvp and locking dvp, which is also correct if the
		 * locks are still shared.
		 */
		VOP_UNLOCK(ldvp, 0);
		vn_lock(dvp, LK_EXCLUSIVE | LK_RETRY);
	}
	vdrop(ldvp);

	if (error == EJUSTRETURN && (flags & ISLASTCN) != 0 &&
	    (mp->mnt_flag & MNT_RDONLY) != 0 &&
	    (cnp->cn_nameiop == CREATE || cnp->cn_nameiop == RENAME))
		error = EROFS;

	if ((error == 0 || error == EJUSTRETURN) && lvp != NULL) {
		if (ldvp == lvp) {
			*ap->a_vpp = dvp;
			VREF(dvp);
			vrele(lvp);
		} else {
			error = null_nodeget(mp, lvp, &vp);
			if (error == 0)
				*ap->a_vpp = vp;
		}
	}
	return (error);
}