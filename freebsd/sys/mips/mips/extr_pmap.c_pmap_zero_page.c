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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ MIPS_DIRECT_MAPPABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ MIPS_PHYS_TO_DIRECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_dcache_wbinv_range (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_lmem_map1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_lmem_unmap () ; 

void
pmap_zero_page(vm_page_t m)
{
	vm_offset_t va;
	vm_paddr_t phys = VM_PAGE_TO_PHYS(m);

	if (MIPS_DIRECT_MAPPABLE(phys)) {
		va = MIPS_PHYS_TO_DIRECT(phys);
		bzero((caddr_t)va, PAGE_SIZE);
		mips_dcache_wbinv_range(va, PAGE_SIZE);
	} else {
		va = pmap_lmem_map1(phys);
		bzero((caddr_t)va, PAGE_SIZE);
		mips_dcache_wbinv_range(va, PAGE_SIZE);
		pmap_lmem_unmap();
	}
}