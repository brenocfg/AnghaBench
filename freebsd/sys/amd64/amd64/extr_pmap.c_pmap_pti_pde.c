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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pdp_entry_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int PAGE_MASK ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int X86_PG_PS ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 int /*<<< orphan*/  pmap_pde_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pti_alloc_page () ; 
 int /*<<< orphan*/  pmap_pti_free_page (int /*<<< orphan*/ ) ; 
 int* pmap_pti_pdpe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pti_obj ; 

__attribute__((used)) static pd_entry_t *
pmap_pti_pde(vm_offset_t va)
{
	pdp_entry_t *pdpe;
	pd_entry_t *pde;
	vm_page_t m;
	vm_pindex_t pd_idx;
	vm_paddr_t mphys;

	VM_OBJECT_ASSERT_WLOCKED(pti_obj);

	pdpe = pmap_pti_pdpe(va);
	if (*pdpe == 0) {
		m = pmap_pti_alloc_page();
		if (*pdpe != 0) {
			pmap_pti_free_page(m);
			MPASS((*pdpe & X86_PG_PS) == 0);
			mphys = *pdpe & ~PAGE_MASK;
		} else {
			mphys =  VM_PAGE_TO_PHYS(m);
			*pdpe = mphys | X86_PG_RW | X86_PG_V;
		}
	} else {
		MPASS((*pdpe & X86_PG_PS) == 0);
		mphys = *pdpe & ~PAGE_MASK;
	}

	pde = (pd_entry_t *)PHYS_TO_DMAP(mphys);
	pd_idx = pmap_pde_index(va);
	pde += pd_idx;
	return (pde);
}