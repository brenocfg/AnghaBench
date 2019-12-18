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
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 scalar_t__ cacheline_size ; 
 int /*<<< orphan*/  hw_direct_map ; 
 int /*<<< orphan*/  moea64_scratchpage_mtx ; 
 scalar_t__* moea64_scratchpage_va ; 
 int /*<<< orphan*/  moea64_set_scratchpage_pa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
moea64_zero_page(mmu_t mmu, vm_page_t m)
{
	vm_paddr_t pa = VM_PAGE_TO_PHYS(m);
	vm_offset_t va, off;

	if (!hw_direct_map) {
		mtx_lock(&moea64_scratchpage_mtx);

		moea64_set_scratchpage_pa(mmu, 0, pa);
		va = moea64_scratchpage_va[0];
	} else {
		va = PHYS_TO_DMAP(pa);
	}

	for (off = 0; off < PAGE_SIZE; off += cacheline_size)
		__asm __volatile("dcbz 0,%0" :: "r"(va + off));

	if (!hw_direct_map)
		mtx_unlock(&moea64_scratchpage_mtx);
}