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
struct vop_need_inactive_args {struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; struct vm_object* v_object; } ;
struct vm_object {scalar_t__ generation; scalar_t__ cleangeneration; } ;
struct tmpfs_node {scalar_t__ tn_links; } ;

/* Variables and functions */
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 scalar_t__ VREG ; 

__attribute__((used)) static int
tmpfs_need_inactive(struct vop_need_inactive_args *ap)
{
	struct vnode *vp;
	struct tmpfs_node *node;
	struct vm_object *obj;

	vp = ap->a_vp;
	node = VP_TO_TMPFS_NODE(vp);
	if (node->tn_links == 0)
		goto need;
	if (vp->v_type == VREG) {
		obj = vp->v_object;
		if (obj->generation != obj->cleangeneration)
			goto need;
	}
	return (0);
need:
	return (1);
}