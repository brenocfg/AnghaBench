#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_11__ {int oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OBJT_DEVICE ; 
 scalar_t__ OBJT_MGTDEVICE ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  dev_pager_free_page (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_remove_all (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 

void
cdev_pager_free_page(vm_object_t object, vm_page_t m)
{

	VM_OBJECT_ASSERT_WLOCKED(object);
	if (object->type == OBJT_MGTDEVICE) {
		KASSERT((m->oflags & VPO_UNMANAGED) == 0, ("unmanaged %p", m));
		pmap_remove_all(m);
		(void)vm_page_remove(m);
		vm_page_xunbusy(m);
	} else if (object->type == OBJT_DEVICE)
		dev_pager_free_page(object, m);
}