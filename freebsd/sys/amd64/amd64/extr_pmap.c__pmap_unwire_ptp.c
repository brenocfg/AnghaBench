#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct spglist {int dummy; } ;
typedef  int pml4_entry_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int pdp_entry_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_15__ {int* pm_pml4u; } ;
struct TYPE_14__ {scalar_t__ pindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ NUPDE ; 
 scalar_t__ NUPDPE ; 
 int PG_FRAME ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  pmap_add_delayed_free_list (TYPE_1__*,struct spglist*,int /*<<< orphan*/ ) ; 
 scalar_t__* pmap_pde (TYPE_2__*,scalar_t__) ; 
 int* pmap_pdpe (TYPE_2__*,scalar_t__) ; 
 int* pmap_pml4e (TYPE_2__*,scalar_t__) ; 
 size_t pmap_pml4e_index (scalar_t__) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pmap_unwire_ptp (TYPE_2__*,scalar_t__,TYPE_1__*,struct spglist*) ; 

__attribute__((used)) static void
_pmap_unwire_ptp(pmap_t pmap, vm_offset_t va, vm_page_t m, struct spglist *free)
{

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	/*
	 * unmap the page table page
	 */
	if (m->pindex >= (NUPDE + NUPDPE)) {
		/* PDP page */
		pml4_entry_t *pml4;
		pml4 = pmap_pml4e(pmap, va);
		*pml4 = 0;
		if (pmap->pm_pml4u != NULL && va <= VM_MAXUSER_ADDRESS) {
			pml4 = &pmap->pm_pml4u[pmap_pml4e_index(va)];
			*pml4 = 0;
		}
	} else if (m->pindex >= NUPDE) {
		/* PD page */
		pdp_entry_t *pdp;
		pdp = pmap_pdpe(pmap, va);
		*pdp = 0;
	} else {
		/* PTE page */
		pd_entry_t *pd;
		pd = pmap_pde(pmap, va);
		*pd = 0;
	}
	pmap_resident_count_dec(pmap, 1);
	if (m->pindex < NUPDE) {
		/* We just released a PT, unhold the matching PD */
		vm_page_t pdpg;

		pdpg = PHYS_TO_VM_PAGE(*pmap_pdpe(pmap, va) & PG_FRAME);
		pmap_unwire_ptp(pmap, va, pdpg, free);
	}
	if (m->pindex >= NUPDE && m->pindex < (NUPDE + NUPDPE)) {
		/* We just released a PD, unhold the matching PDP */
		vm_page_t pdppg;

		pdppg = PHYS_TO_VM_PAGE(*pmap_pml4e(pmap, va) & PG_FRAME);
		pmap_unwire_ptp(pmap, va, pdppg, free);
	}

	/* 
	 * Put page on a list so that it is released after
	 * *ALL* TLB shootdown is done
	 */
	pmap_add_delayed_free_list(m, free, TRUE);
}