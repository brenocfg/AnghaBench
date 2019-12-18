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
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/ * pd_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_DIRECT_TO_PHYS (int /*<<< orphan*/ *) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int PMAP_ENTER_NOSLEEP ; 
 TYPE_1__* _pmap_allocpte (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/ ** pmap_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int pmap_pde_pindex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_page_t
pmap_allocpte(pmap_t pmap, vm_offset_t va, u_int flags)
{
	unsigned ptepindex;
	pd_entry_t *pde;
	vm_page_t m;

	/*
	 * Calculate pagetable page index
	 */
	ptepindex = pmap_pde_pindex(va);
retry:
	/*
	 * Get the page directory entry
	 */
	pde = pmap_pde(pmap, va);

	/*
	 * If the page table page is mapped, we just increment the hold
	 * count, and activate it.
	 */
	if (pde != NULL && *pde != NULL) {
		m = PHYS_TO_VM_PAGE(MIPS_DIRECT_TO_PHYS(*pde));
		m->ref_count++;
	} else {
		/*
		 * Here if the pte page isn't mapped, or if it has been
		 * deallocated.
		 */
		m = _pmap_allocpte(pmap, ptepindex, flags);
		if (m == NULL && (flags & PMAP_ENTER_NOSLEEP) == 0)
			goto retry;
	}
	return (m);
}