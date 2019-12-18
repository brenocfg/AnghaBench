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
struct TYPE_5__ {int ref_count; struct TYPE_5__* backing_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBSC_COLLAPSE_NOWAIT ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_collapse_scan (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_object_qcollapse(vm_object_t object)
{
	vm_object_t backing_object = object->backing_object;

	VM_OBJECT_ASSERT_WLOCKED(object);
	VM_OBJECT_ASSERT_WLOCKED(backing_object);

	if (backing_object->ref_count != 1)
		return;

	vm_object_collapse_scan(object, OBSC_COLLAPSE_NOWAIT);
}