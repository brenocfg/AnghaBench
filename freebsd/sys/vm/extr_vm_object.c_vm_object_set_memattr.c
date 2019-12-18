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
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct TYPE_5__ {int type; int /*<<< orphan*/  memattr; int /*<<< orphan*/  memq; } ;

/* Variables and functions */
 int KERN_FAILURE ; 
 int KERN_INVALID_ARGUMENT ; 
 int KERN_SUCCESS ; 
#define  OBJT_DEAD 135 
#define  OBJT_DEFAULT 134 
#define  OBJT_DEVICE 133 
#define  OBJT_MGTDEVICE 132 
#define  OBJT_PHYS 131 
#define  OBJT_SG 130 
#define  OBJT_SWAP 129 
#define  OBJT_VNODE 128 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 

int
vm_object_set_memattr(vm_object_t object, vm_memattr_t memattr)
{

	VM_OBJECT_ASSERT_WLOCKED(object);
	switch (object->type) {
	case OBJT_DEFAULT:
	case OBJT_DEVICE:
	case OBJT_MGTDEVICE:
	case OBJT_PHYS:
	case OBJT_SG:
	case OBJT_SWAP:
	case OBJT_VNODE:
		if (!TAILQ_EMPTY(&object->memq))
			return (KERN_FAILURE);
		break;
	case OBJT_DEAD:
		return (KERN_INVALID_ARGUMENT);
	default:
		panic("vm_object_set_memattr: object %p is of undefined type",
		    object);
	}
	object->memattr = memattr;
	return (KERN_SUCCESS);
}