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
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int PAGE_MASK ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int X86_PG_PS ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 int pg_nx ; 
 int /*<<< orphan*/  pmap_pte_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pti_alloc_page () ; 
 int /*<<< orphan*/  pmap_pti_free_page (int /*<<< orphan*/ ) ; 
 int* pmap_pti_pde (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pti_wire_pte (int*) ; 
 int /*<<< orphan*/  pti_obj ; 

__attribute__((used)) static pt_entry_t *
pmap_pti_pte(vm_offset_t va, bool *unwire_pde)
{
	pd_entry_t *pde;
	pt_entry_t *pte;
	vm_page_t m;
	vm_paddr_t mphys;

	VM_OBJECT_ASSERT_WLOCKED(pti_obj);

	pde = pmap_pti_pde(va);
	if (unwire_pde != NULL) {
		*unwire_pde = true;
		pmap_pti_wire_pte(pde);
	}
	if (*pde == 0) {
		m = pmap_pti_alloc_page();
		if (*pde != 0) {
			pmap_pti_free_page(m);
			MPASS((*pde & X86_PG_PS) == 0);
			mphys = *pde & ~(PAGE_MASK | pg_nx);
		} else {
			mphys = VM_PAGE_TO_PHYS(m);
			*pde = mphys | X86_PG_RW | X86_PG_V;
			if (unwire_pde != NULL)
				*unwire_pde = false;
		}
	} else {
		MPASS((*pde & X86_PG_PS) == 0);
		mphys = *pde & ~(PAGE_MASK | pg_nx);
	}

	pte = (pt_entry_t *)PHYS_TO_DMAP(mphys);
	pte += pmap_pte_index(va);

	return (pte);
}