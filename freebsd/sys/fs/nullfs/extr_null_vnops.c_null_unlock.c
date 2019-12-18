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
struct vop_unlock_args {struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct null_node {int dummy; } ;

/* Variables and functions */
 struct vnode* NULLVPTOLOWERVP (struct vnode*) ; 
 int VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct null_node* VTONULL (struct vnode*) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vholdnz (struct vnode*) ; 
 int vop_stdunlock (struct vop_unlock_args*) ; 

__attribute__((used)) static int
null_unlock(struct vop_unlock_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct null_node *nn;
	struct vnode *lvp;
	int error;

	nn = VTONULL(vp);
	if (nn != NULL && (lvp = NULLVPTOLOWERVP(vp)) != NULL) {
		vholdnz(lvp);
		error = VOP_UNLOCK(lvp, 0);
		vdrop(lvp);
	} else {
		error = vop_stdunlock(ap);
	}

	return (error);
}