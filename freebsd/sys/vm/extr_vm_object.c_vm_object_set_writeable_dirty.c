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
struct TYPE_4__ {scalar_t__ type; int flags; int /*<<< orphan*/  generation; } ;

/* Variables and functions */
 scalar_t__ OBJT_VNODE ; 
 int OBJ_TMPFS_NODE ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 

void
vm_object_set_writeable_dirty(vm_object_t object)
{

	VM_OBJECT_ASSERT_LOCKED(object);

	/* Only set for vnodes & tmpfs */
	if (object->type != OBJT_VNODE &&
	    (object->flags & OBJ_TMPFS_NODE) == 0)
		return;
	atomic_add_int(&object->generation, 1);
}