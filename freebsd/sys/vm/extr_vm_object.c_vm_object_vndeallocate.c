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
typedef  TYPE_1__* vm_object_t ;
struct vnode {int dummy; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  ref_count; scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OBJT_VNODE ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (TYPE_1__*) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_shm_object_terminated (TYPE_1__*) ; 
 int /*<<< orphan*/  umtx_shm_vnobj_persistent ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static void
vm_object_vndeallocate(vm_object_t object)
{
	struct vnode *vp = (struct vnode *) object->handle;

	KASSERT(object->type == OBJT_VNODE,
	    ("vm_object_vndeallocate: not a vnode object"));
	KASSERT(vp != NULL, ("vm_object_vndeallocate: missing vp"));

	if (refcount_release(&object->ref_count) &&
	    !umtx_shm_vnobj_persistent)
		umtx_shm_object_terminated(object);

	VM_OBJECT_RUNLOCK(object);
	/* vrele may need the vnode lock. */
	vrele(vp);
}