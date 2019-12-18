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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  TYPE_1__* vm_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  rtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_radix_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

vm_page_t
vm_page_lookup(vm_object_t object, vm_pindex_t pindex)
{

	VM_OBJECT_ASSERT_LOCKED(object);
	return (vm_radix_lookup(&object->rtree, pindex));
}