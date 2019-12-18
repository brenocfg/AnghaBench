#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct vop_setattr_args {int /*<<< orphan*/  a_cred; TYPE_4__* a_vp; struct vattr* a_vap; } ;
struct vnode {scalar_t__ v_type; } ;
struct TYPE_8__ {scalar_t__ tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_sec; } ;
struct vattr {scalar_t__ va_flags; scalar_t__ va_uid; scalar_t__ va_gid; scalar_t__ va_mode; scalar_t__ va_size; TYPE_3__ va_mtime; TYPE_2__ va_atime; } ;
struct unionfs_node {struct vnode* un_uppervp; struct vnode* un_lowervp; } ;
struct thread {int dummy; } ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_9__ {TYPE_1__* v_mount; } ;
struct TYPE_6__ {int mnt_flag; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (TYPE_4__*) ; 
 int MNT_RDONLY ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 scalar_t__ VNOVAL ; 
 int VOP_SETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 struct unionfs_node* VTOUNIONFS (TYPE_4__*) ; 
 struct thread* curthread ; 
 int unionfs_copyfile (struct unionfs_node*,int,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
unionfs_setattr(struct vop_setattr_args *ap)
{
	int		error;
	struct unionfs_node *unp;
	struct vnode   *uvp;
	struct vnode   *lvp;
	struct thread  *td;
	struct vattr   *vap;

	UNIONFS_INTERNAL_DEBUG("unionfs_setattr: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	error = EROFS;
	unp = VTOUNIONFS(ap->a_vp);
	uvp = unp->un_uppervp;
	lvp = unp->un_lowervp;
	td = curthread;
	vap = ap->a_vap;

	if ((ap->a_vp->v_mount->mnt_flag & MNT_RDONLY) &&
	    (vap->va_flags != VNOVAL || vap->va_uid != (uid_t)VNOVAL ||
	     vap->va_gid != (gid_t)VNOVAL || vap->va_atime.tv_sec != VNOVAL ||
	     vap->va_mtime.tv_sec != VNOVAL || vap->va_mode != (mode_t)VNOVAL))
		return (EROFS);

	if (uvp == NULLVP && lvp->v_type == VREG) {
		error = unionfs_copyfile(unp, (vap->va_size != 0),
		    ap->a_cred, td);
		if (error != 0)
			return (error);
		uvp = unp->un_uppervp;
	}

	if (uvp != NULLVP)
		error = VOP_SETATTR(uvp, vap, ap->a_cred);

	UNIONFS_INTERNAL_DEBUG("unionfs_setattr: leave (%d)\n", error);

	return (error);
}