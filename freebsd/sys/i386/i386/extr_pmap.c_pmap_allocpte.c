#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  size_t vm_offset_t ;
typedef  size_t u_int ;
typedef  TYPE_2__* pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_10__ {int* pm_pdir; } ;
struct TYPE_9__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 size_t PDRSHIFT ; 
 int PG_FRAME ; 
 int PG_PS ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int) ; 
 size_t PMAP_ENTER_NOSLEEP ; 
 TYPE_1__* _pmap_allocpte (TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  pmap_demote_pde (TYPE_2__*,int*,size_t) ; 

__attribute__((used)) static vm_page_t
pmap_allocpte(pmap_t pmap, vm_offset_t va, u_int flags)
{
	u_int ptepindex;
	pd_entry_t ptepa;
	vm_page_t m;

	/*
	 * Calculate pagetable page index
	 */
	ptepindex = va >> PDRSHIFT;
retry:
	/*
	 * Get the page directory entry
	 */
	ptepa = pmap->pm_pdir[ptepindex];

	/*
	 * This supports switching from a 4MB page to a
	 * normal 4K page.
	 */
	if (ptepa & PG_PS) {
		(void)pmap_demote_pde(pmap, &pmap->pm_pdir[ptepindex], va);
		ptepa = pmap->pm_pdir[ptepindex];
	}

	/*
	 * If the page table page is mapped, we just increment the
	 * hold count, and activate it.
	 */
	if (ptepa) {
		m = PHYS_TO_VM_PAGE(ptepa & PG_FRAME);
		m->ref_count++;
	} else {
		/*
		 * Here if the pte page isn't mapped, or if it has
		 * been deallocated. 
		 */
		m = _pmap_allocpte(pmap, ptepindex, flags);
		if (m == NULL && (flags & PMAP_ENTER_NOSLEEP) == 0)
			goto retry;
	}
	return (m);
}