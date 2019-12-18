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
struct vop_remove_args {struct vnode* a_vp; struct componentname* a_cnp; struct vnode* a_dvp; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; int /*<<< orphan*/ * v_op; } ;
struct unionfs_node {char* un_path; struct vnode* un_lowervp; struct vnode* un_uppervp; } ;
struct unionfs_mount {scalar_t__ um_whitemode; } ;
struct thread {int dummy; } ;
struct componentname {char* cn_nameptr; int /*<<< orphan*/  cn_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  DOWHITEOUT ; 
 int EINVAL ; 
 int ENOENT ; 
 int EROFS ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (struct vnode*) ; 
 int LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_RELEASE ; 
 int LK_RETRY ; 
 struct unionfs_mount* MOUNTTOUNIONFSMOUNT (int /*<<< orphan*/ ) ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 scalar_t__ UNIONFS_WHITE_ALWAYS ; 
 int VOP_REMOVE (struct vnode*,struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ VSOCK ; 
 struct unionfs_node* VTOUNIONFS (struct vnode*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int unionfs_mkwhiteout (struct vnode*,struct componentname*,struct thread*,char*) ; 
 int unionfs_relookup (struct vnode*,struct vnode**,struct componentname*,struct componentname*,struct thread*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unionfs_vnodeops ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
unionfs_remove(struct vop_remove_args *ap)
{
	int		error;
	char	       *path;
	struct unionfs_node *dunp;
	struct unionfs_node *unp;
	struct unionfs_mount *ump;
	struct vnode   *udvp;
	struct vnode   *uvp;
	struct vnode   *lvp;
	struct vnode   *vp;
	struct componentname *cnp;
	struct componentname cn;
	struct thread  *td;

	UNIONFS_INTERNAL_DEBUG("unionfs_remove: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_dvp);

	error = 0;
	dunp = VTOUNIONFS(ap->a_dvp);
	udvp = dunp->un_uppervp;
	cnp = ap->a_cnp;
	td = curthread;

	if (ap->a_vp->v_op != &unionfs_vnodeops) {
		if (ap->a_vp->v_type != VSOCK)
			return (EINVAL);
		ump = NULL;
		vp = uvp = lvp = NULLVP;
		/* search vnode */
		VOP_UNLOCK(ap->a_vp, LK_RELEASE);
		error = unionfs_relookup(udvp, &vp, cnp, &cn, td,
		    cnp->cn_nameptr, strlen(cnp->cn_nameptr), DELETE);
		if (error != 0 && error != ENOENT) {
			vn_lock(ap->a_vp, LK_EXCLUSIVE | LK_RETRY);
			return (error);
		}

		if (error == 0 && vp == ap->a_vp) {
			/* target vnode in upper */
			uvp = vp;
			vrele(vp);
			path = NULL;
		} else {
			/* target vnode in lower */
			if (vp != NULLVP) {
				if (udvp == vp)
					vrele(vp);
				else
					vput(vp);
			}
			vn_lock(ap->a_vp, LK_EXCLUSIVE | LK_RETRY);
			lvp = ap->a_vp;
			path = ap->a_cnp->cn_nameptr;
		}
	} else {
		ump = MOUNTTOUNIONFSMOUNT(ap->a_vp->v_mount);
		unp = VTOUNIONFS(ap->a_vp);
		uvp = unp->un_uppervp;
		lvp = unp->un_lowervp;
		path = unp->un_path;
	}

	if (udvp == NULLVP)
		return (EROFS);

	if (uvp != NULLVP) {
		/*
		 * XXX: if the vnode type is VSOCK, it will create whiteout
		 *      after remove.
		 */
		if (ump == NULL || ump->um_whitemode == UNIONFS_WHITE_ALWAYS ||
		    lvp != NULLVP)
			cnp->cn_flags |= DOWHITEOUT;
		error = VOP_REMOVE(udvp, uvp, cnp);
	} else if (lvp != NULLVP)
		error = unionfs_mkwhiteout(udvp, cnp, td, path);

	UNIONFS_INTERNAL_DEBUG("unionfs_remove: leave (%d)\n", error);

	return (error);
}