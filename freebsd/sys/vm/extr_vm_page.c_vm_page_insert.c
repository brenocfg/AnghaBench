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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  TYPE_1__* vm_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  rtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_1__*) ; 
 int vm_page_insert_after (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_radix_lookup_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
vm_page_insert(vm_page_t m, vm_object_t object, vm_pindex_t pindex)
{
	vm_page_t mpred;

	VM_OBJECT_ASSERT_WLOCKED(object);
	mpred = vm_radix_lookup_le(&object->rtree, pindex);
	return (vm_page_insert_after(m, object, pindex, mpred));
}