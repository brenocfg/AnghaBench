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
typedef  int /*<<< orphan*/  mmu_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 scalar_t__ hw_direct_map ; 
 int /*<<< orphan*/  moea64_scratchpage_mtx ; 
 scalar_t__* moea64_scratchpage_va ; 
 int /*<<< orphan*/  moea64_set_scratchpage_pa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
moea64_zero_page_area(mmu_t mmu, vm_page_t m, int off, int size)
{
	vm_paddr_t pa = VM_PAGE_TO_PHYS(m);

	if (size + off > PAGE_SIZE)
		panic("moea64_zero_page: size + off > PAGE_SIZE");

	if (hw_direct_map) {
		bzero((caddr_t)(uintptr_t)PHYS_TO_DMAP(pa) + off, size);
	} else {
		mtx_lock(&moea64_scratchpage_mtx);
		moea64_set_scratchpage_pa(mmu, 0, pa);
		bzero((caddr_t)moea64_scratchpage_va[0] + off, size);
		mtx_unlock(&moea64_scratchpage_mtx);
	}
}