#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
struct vnode {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; struct vnode* handle; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ OBJT_VNODE ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 

void
vm_object_reference_locked(vm_object_t object)
{
	struct vnode *vp;

	VM_OBJECT_ASSERT_LOCKED(object);
	refcount_acquire(&object->ref_count);
	if (object->type == OBJT_VNODE) {
		vp = object->handle;
		vref(vp);
	}
}