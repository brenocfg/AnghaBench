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
typedef  int vm_offset_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_dcache_wbinv_range_index (int,int) ; 
 int /*<<< orphan*/  pmap_flush_pvcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kenter (int,int /*<<< orphan*/ ) ; 

void
pmap_qenter(vm_offset_t va, vm_page_t *m, int count)
{
	int i;
	vm_offset_t origva = va;

	for (i = 0; i < count; i++) {
		pmap_flush_pvcache(m[i]);
		pmap_kenter(va, VM_PAGE_TO_PHYS(m[i]));
		va += PAGE_SIZE;
	}

	mips_dcache_wbinv_range_index(origva, PAGE_SIZE*count);
}