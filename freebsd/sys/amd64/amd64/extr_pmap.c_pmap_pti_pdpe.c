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
typedef  size_t vm_pindex_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pml4_entry_t ;
typedef  int /*<<< orphan*/  pdp_entry_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ *) ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pmap_pdpe_index (int /*<<< orphan*/ ) ; 
 size_t pmap_pml4e_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pti_alloc_page () ; 
 int /*<<< orphan*/  pmap_pti_free_page (int /*<<< orphan*/ *) ; 
 scalar_t__ pti_finalized ; 
 int /*<<< orphan*/  pti_obj ; 
 int* pti_pml4 ; 

__attribute__((used)) static pdp_entry_t *
pmap_pti_pdpe(vm_offset_t va)
{
	pml4_entry_t *pml4e;
	pdp_entry_t *pdpe;
	vm_page_t m;
	vm_pindex_t pml4_idx;
	vm_paddr_t mphys;

	VM_OBJECT_ASSERT_WLOCKED(pti_obj);

	pml4_idx = pmap_pml4e_index(va);
	pml4e = &pti_pml4[pml4_idx];
	m = NULL;
	if (*pml4e == 0) {
		if (pti_finalized)
			panic("pml4 alloc after finalization\n");
		m = pmap_pti_alloc_page();
		if (*pml4e != 0) {
			pmap_pti_free_page(m);
			mphys = *pml4e & ~PAGE_MASK;
		} else {
			mphys = VM_PAGE_TO_PHYS(m);
			*pml4e = mphys | X86_PG_RW | X86_PG_V;
		}
	} else {
		mphys = *pml4e & ~PAGE_MASK;
	}
	pdpe = (pdp_entry_t *)PHYS_TO_DMAP(mphys) + pmap_pdpe_index(va);
	return (pdpe);
}