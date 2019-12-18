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
struct TYPE_5__ {int type; int flags; } ;

/* Variables and functions */
 int KVME_TYPE_DEAD ; 
 int KVME_TYPE_DEFAULT ; 
 int KVME_TYPE_DEVICE ; 
 int KVME_TYPE_MGTDEVICE ; 
 int KVME_TYPE_PHYS ; 
 int KVME_TYPE_SG ; 
 int KVME_TYPE_SWAP ; 
 int KVME_TYPE_UNKNOWN ; 
 int KVME_TYPE_VNODE ; 
#define  OBJT_DEAD 135 
#define  OBJT_DEFAULT 134 
#define  OBJT_DEVICE 133 
#define  OBJT_MGTDEVICE 132 
#define  OBJT_PHYS 131 
#define  OBJT_SG 130 
#define  OBJT_SWAP 129 
#define  OBJT_VNODE 128 
 int OBJ_TMPFS_NODE ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (TYPE_1__*) ; 
 struct vnode* vm_object_vnode (TYPE_1__*) ; 

int
vm_object_kvme_type(vm_object_t object, struct vnode **vpp)
{

	VM_OBJECT_ASSERT_LOCKED(object);
	if (vpp != NULL)
		*vpp = vm_object_vnode(object);
	switch (object->type) {
	case OBJT_DEFAULT:
		return (KVME_TYPE_DEFAULT);
	case OBJT_VNODE:
		return (KVME_TYPE_VNODE);
	case OBJT_SWAP:
		if ((object->flags & OBJ_TMPFS_NODE) != 0)
			return (KVME_TYPE_VNODE);
		return (KVME_TYPE_SWAP);
	case OBJT_DEVICE:
		return (KVME_TYPE_DEVICE);
	case OBJT_PHYS:
		return (KVME_TYPE_PHYS);
	case OBJT_DEAD:
		return (KVME_TYPE_DEAD);
	case OBJT_SG:
		return (KVME_TYPE_SG);
	case OBJT_MGTDEVICE:
		return (KVME_TYPE_MGTDEVICE);
	default:
		return (KVME_TYPE_UNKNOWN);
	}
}