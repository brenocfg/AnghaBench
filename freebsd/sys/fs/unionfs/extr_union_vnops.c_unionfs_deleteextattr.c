#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vop_deleteextattr_args {struct thread* a_td; struct ucred* a_cred; int /*<<< orphan*/  a_name; int /*<<< orphan*/  a_attrnamespace; TYPE_2__* a_vp; } ;
struct vnode {scalar_t__ v_type; } ;
struct unionfs_node {int un_flag; struct vnode* un_uppervp; struct vnode* un_lowervp; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_5__ {TYPE_1__* v_mount; } ;
struct TYPE_4__ {int mnt_flag; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EROFS ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (TYPE_2__*) ; 
 int MNT_RDONLY ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,int) ; 
 int UNIONFS_OPENEXTL ; 
 int UNIONFS_OPENEXTU ; 
 int /*<<< orphan*/  VOP_CLOSEEXTATTR (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int VOP_DELETEEXTATTR (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int VOP_OPENEXTATTR (struct vnode*,struct ucred*,struct thread*) ; 
 scalar_t__ VREG ; 
 struct unionfs_node* VTOUNIONFS (TYPE_2__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int unionfs_copyfile (struct unionfs_node*,int,struct ucred*,struct thread*) ; 

__attribute__((used)) static int
unionfs_deleteextattr(struct vop_deleteextattr_args *ap)
{
	int		error;
	struct unionfs_node *unp;
	struct vnode   *uvp;
	struct vnode   *lvp;
	struct vnode   *ovp;
	struct ucred   *cred;
	struct thread  *td;

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	error = EROFS;
	unp = VTOUNIONFS(ap->a_vp);
	uvp = unp->un_uppervp;
	lvp = unp->un_lowervp;
	ovp = NULLVP;
	cred = ap->a_cred;
	td = ap->a_td;

	UNIONFS_INTERNAL_DEBUG("unionfs_deleteextattr: enter (un_flag=%x)\n", unp->un_flag);

	if (ap->a_vp->v_mount->mnt_flag & MNT_RDONLY)
		return (EROFS);

	if (unp->un_flag & UNIONFS_OPENEXTU)
		ovp = unp->un_uppervp;
	else if (unp->un_flag & UNIONFS_OPENEXTL)
		ovp = unp->un_lowervp;

	if (ovp == NULLVP)
		return (EOPNOTSUPP);

	if (ovp == lvp && lvp->v_type == VREG) {
		VOP_CLOSEEXTATTR(lvp, 0, cred, td);
		if (uvp == NULLVP &&
		    (error = unionfs_copyfile(unp, 1, cred, td)) != 0) {
unionfs_deleteextattr_reopen:
			if ((unp->un_flag & UNIONFS_OPENEXTL) &&
			    VOP_OPENEXTATTR(lvp, cred, td)) {
#ifdef DIAGNOSTIC
				panic("unionfs: VOP_OPENEXTATTR failed");
#endif
				unp->un_flag &= ~UNIONFS_OPENEXTL;
			}
			goto unionfs_deleteextattr_abort;
		}
		uvp = unp->un_uppervp;
		if ((error = VOP_OPENEXTATTR(uvp, cred, td)) != 0)
			goto unionfs_deleteextattr_reopen;
		unp->un_flag &= ~UNIONFS_OPENEXTL;
		unp->un_flag |= UNIONFS_OPENEXTU;
		ovp = uvp;
	}

	if (ovp == uvp)
		error = VOP_DELETEEXTATTR(ovp, ap->a_attrnamespace, ap->a_name,
		    ap->a_cred, ap->a_td);

unionfs_deleteextattr_abort:
	UNIONFS_INTERNAL_DEBUG("unionfs_deleteextattr: leave (%d)\n", error);

	return (error);
}