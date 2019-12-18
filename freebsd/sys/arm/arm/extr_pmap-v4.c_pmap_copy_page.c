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
typedef  int /*<<< orphan*/  vm_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PHYSICAL ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 scalar_t__ _arm_memcpy (void*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ _min_memcpy_size ; 
 int /*<<< orphan*/  cpu_dcache_wbinv_all () ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_all () ; 
 int /*<<< orphan*/  pmap_copy_page_generic (scalar_t__,scalar_t__) ; 

void
pmap_copy_page(vm_page_t src, vm_page_t dst)
{

	cpu_dcache_wbinv_all();
	cpu_l2cache_wbinv_all();
	if (_arm_memcpy && PAGE_SIZE >= _min_memcpy_size &&
	    _arm_memcpy((void *)VM_PAGE_TO_PHYS(dst),
	    (void *)VM_PAGE_TO_PHYS(src), PAGE_SIZE, IS_PHYSICAL) == 0)
		return;
	pmap_copy_page_generic(VM_PAGE_TO_PHYS(src), VM_PAGE_TO_PHYS(dst));
}