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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ NBPDR ; 
 int NPDEPG ; 
 int PDPSHIFT ; 
 int PG_PS ; 
 int PG_U ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_ALLOC_INTERRUPT ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ *) ; 
 int pmap_accessed_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int) ; 
 int pmap_modified_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pdpe_demotions ; 
 int pmap_rw_bit (int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_page_alloc (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ vtopde (int) ; 

__attribute__((used)) static boolean_t
pmap_demote_pdpe(pmap_t pmap, pdp_entry_t *pdpe, vm_offset_t va)
{
	pdp_entry_t newpdpe, oldpdpe;
	pd_entry_t *firstpde, newpde, *pde;
	pt_entry_t PG_A, PG_M, PG_RW, PG_V;
	vm_paddr_t pdpgpa;
	vm_page_t pdpg;

	PG_A = pmap_accessed_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_V = pmap_valid_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	oldpdpe = *pdpe;
	KASSERT((oldpdpe & (PG_PS | PG_V)) == (PG_PS | PG_V),
	    ("pmap_demote_pdpe: oldpdpe is missing PG_PS and/or PG_V"));
	if ((pdpg = vm_page_alloc(NULL, va >> PDPSHIFT, VM_ALLOC_INTERRUPT |
	    VM_ALLOC_NOOBJ | VM_ALLOC_WIRED)) == NULL) {
		CTR2(KTR_PMAP, "pmap_demote_pdpe: failure for va %#lx"
		    " in pmap %p", va, pmap);
		return (FALSE);
	}
	pdpgpa = VM_PAGE_TO_PHYS(pdpg);
	firstpde = (pd_entry_t *)PHYS_TO_DMAP(pdpgpa);
	newpdpe = pdpgpa | PG_M | PG_A | (oldpdpe & PG_U) | PG_RW | PG_V;
	KASSERT((oldpdpe & PG_A) != 0,
	    ("pmap_demote_pdpe: oldpdpe is missing PG_A"));
	KASSERT((oldpdpe & (PG_M | PG_RW)) != PG_RW,
	    ("pmap_demote_pdpe: oldpdpe is missing PG_M"));
	newpde = oldpdpe;

	/*
	 * Initialize the page directory page.
	 */
	for (pde = firstpde; pde < firstpde + NPDEPG; pde++) {
		*pde = newpde;
		newpde += NBPDR;
	}

	/*
	 * Demote the mapping.
	 */
	*pdpe = newpdpe;

	/*
	 * Invalidate a stale recursive mapping of the page directory page.
	 */
	pmap_invalidate_page(pmap, (vm_offset_t)vtopde(va));

	pmap_pdpe_demotions++;
	CTR2(KTR_PMAP, "pmap_demote_pdpe: success for va %#lx"
	    " in pmap %p", va, pmap);
	return (TRUE);
}