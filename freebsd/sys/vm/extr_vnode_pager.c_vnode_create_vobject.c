#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_ooffset_t ;
typedef  TYPE_1__* vm_object_t ;
struct vnode {TYPE_1__* v_object; } ;
struct vattr {scalar_t__ va_size; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IDX_TO_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (TYPE_1__*) ; 
 scalar_t__ VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 scalar_t__ vn_canvmio (struct vnode*) ; 
 scalar_t__ vn_isdisk (struct vnode*,int /*<<< orphan*/ *) ; 
 TYPE_1__* vnode_pager_alloc (struct vnode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
vnode_create_vobject(struct vnode *vp, off_t isize, struct thread *td)
{
	vm_object_t object;
	vm_ooffset_t size = isize;
	struct vattr va;

	if (!vn_isdisk(vp, NULL) && vn_canvmio(vp) == FALSE)
		return (0);

	object = vp->v_object;
	if (object != NULL)
		return (0);

	if (size == 0) {
		if (vn_isdisk(vp, NULL)) {
			size = IDX_TO_OFF(INT_MAX);
		} else {
			if (VOP_GETATTR(vp, &va, td->td_ucred))
				return (0);
			size = va.va_size;
		}
	}

	object = vnode_pager_alloc(vp, size, 0, 0, td->td_ucred);
	/*
	 * Dereference the reference we just created.  This assumes
	 * that the object is associated with the vp.
	 */
	VM_OBJECT_RLOCK(object);
	refcount_release(&object->ref_count);
	VM_OBJECT_RUNLOCK(object);
	vrele(vp);

	KASSERT(vp->v_object != NULL, ("vnode_create_vobject: NULL object"));

	return (0);
}