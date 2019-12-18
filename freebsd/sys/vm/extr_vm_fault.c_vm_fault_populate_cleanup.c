#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_fault_populate_check_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_deactivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_fault_populate_cleanup(vm_object_t object, vm_pindex_t first,
    vm_pindex_t last)
{
	vm_page_t m;
	vm_pindex_t pidx;

	VM_OBJECT_ASSERT_WLOCKED(object);
	MPASS(first <= last);
	for (pidx = first, m = vm_page_lookup(object, pidx);
	    pidx <= last; pidx++, m = vm_page_next(m)) {
		vm_fault_populate_check_page(m);
		vm_page_lock(m);
		vm_page_deactivate(m);
		vm_page_unlock(m);
		vm_page_xunbusy(m);
	}
}