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
struct vnode {scalar_t__ v_type; struct vm_object* v_object; } ;
struct vm_object {int flags; scalar_t__ generation; scalar_t__ cleangeneration; } ;
struct tmpfs_node {int tn_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OBJ_TMPFS ; 
 int OBJ_TMPFS_NODE ; 
 int TMPFS_NODE_CHANGED ; 
 int TMPFS_NODE_MODIFIED ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (struct vm_object*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (struct vm_object*) ; 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 scalar_t__ VREG ; 

void
tmpfs_check_mtime(struct vnode *vp)
{
	struct tmpfs_node *node;
	struct vm_object *obj;

	ASSERT_VOP_ELOCKED(vp, "check_mtime");
	if (vp->v_type != VREG)
		return;
	obj = vp->v_object;
	KASSERT((obj->flags & (OBJ_TMPFS_NODE | OBJ_TMPFS)) ==
	    (OBJ_TMPFS_NODE | OBJ_TMPFS), ("non-tmpfs obj"));
	/* unlocked read */
	if (obj->generation != obj->cleangeneration) {
		VM_OBJECT_WLOCK(obj);
		if (obj->generation != obj->cleangeneration) {
			obj->cleangeneration = obj->generation;
			node = VP_TO_TMPFS_NODE(vp);
			node->tn_status |= TMPFS_NODE_MODIFIED |
			    TMPFS_NODE_CHANGED;
		}
		VM_OBJECT_WUNLOCK(obj);
	}
}