#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bo_flag; } ;
struct vnode {struct vm_object* v_object; TYPE_1__ v_bufobj; } ;
struct vm_object {scalar_t__ type; scalar_t__ ref_count; int flags; struct vnode* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  BO_DEAD ; 
 int /*<<< orphan*/  BO_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  BO_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  OBJPC_SYNC ; 
 scalar_t__ OBJT_VNODE ; 
 int OBJ_DEAD ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (struct vm_object*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (struct vm_object*) ; 
 int /*<<< orphan*/  V_SAVE ; 
 int /*<<< orphan*/  umtx_shm_object_terminated (struct vm_object*) ; 
 int /*<<< orphan*/  vinvalbuf (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_page_clean (struct vm_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_set_flag (struct vm_object*,int) ; 
 int /*<<< orphan*/  vm_object_terminate (struct vm_object*) ; 
 int /*<<< orphan*/  vm_pager_deallocate (struct vm_object*) ; 

void
vnode_destroy_vobject(struct vnode *vp)
{
	struct vm_object *obj;

	obj = vp->v_object;
	if (obj == NULL || obj->handle != vp)
		return;
	ASSERT_VOP_ELOCKED(vp, "vnode_destroy_vobject");
	VM_OBJECT_WLOCK(obj);
	MPASS(obj->type == OBJT_VNODE);
	umtx_shm_object_terminated(obj);
	if (obj->ref_count == 0) {
		/*
		 * don't double-terminate the object
		 */
		if ((obj->flags & OBJ_DEAD) == 0) {
			vm_object_set_flag(obj, OBJ_DEAD);

			/*
			 * Clean pages and flush buffers.
			 */
			vm_object_page_clean(obj, 0, 0, OBJPC_SYNC);
			VM_OBJECT_WUNLOCK(obj);

			vinvalbuf(vp, V_SAVE, 0, 0);

			BO_LOCK(&vp->v_bufobj);
			vp->v_bufobj.bo_flag |= BO_DEAD;
			BO_UNLOCK(&vp->v_bufobj);

			VM_OBJECT_WLOCK(obj);
			vm_object_terminate(obj);
		} else {
			/*
			 * Waiters were already handled during object
			 * termination.  The exclusive vnode lock hopefully
			 * prevented new waiters from referencing the dying
			 * object.
			 */
			vp->v_object = NULL;
			VM_OBJECT_WUNLOCK(obj);
		}
	} else {
		/*
		 * Woe to the process that tries to page now :-).
		 */
		vm_pager_deallocate(obj);
		VM_OBJECT_WUNLOCK(obj);
	}
	KASSERT(vp->v_object == NULL, ("vp %p obj %p", vp, vp->v_object));
}