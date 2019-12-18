#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_6__ {scalar_t__ pindex; } ;

/* Variables and functions */
 int ATTR_MASK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ NUL1E ; 
 scalar_t__ NUL2E ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pmap_add_delayed_free_list (TYPE_1__*,struct spglist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_clear (int*) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_l0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_l1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_l2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_load (int*) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_unwire_l3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct spglist*) ; 

__attribute__((used)) static void
_pmap_unwire_l3(pmap_t pmap, vm_offset_t va, vm_page_t m, struct spglist *free)
{

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	/*
	 * unmap the page table page
	 */
	if (m->pindex >= (NUL2E + NUL1E)) {
		/* l1 page */
		pd_entry_t *l0;

		l0 = pmap_l0(pmap, va);
		pmap_clear(l0);
	} else if (m->pindex >= NUL2E) {
		/* l2 page */
		pd_entry_t *l1;

		l1 = pmap_l1(pmap, va);
		pmap_clear(l1);
	} else {
		/* l3 page */
		pd_entry_t *l2;

		l2 = pmap_l2(pmap, va);
		pmap_clear(l2);
	}
	pmap_resident_count_dec(pmap, 1);
	if (m->pindex < NUL2E) {
		/* We just released an l3, unhold the matching l2 */
		pd_entry_t *l1, tl1;
		vm_page_t l2pg;

		l1 = pmap_l1(pmap, va);
		tl1 = pmap_load(l1);
		l2pg = PHYS_TO_VM_PAGE(tl1 & ~ATTR_MASK);
		pmap_unwire_l3(pmap, va, l2pg, free);
	} else if (m->pindex < (NUL2E + NUL1E)) {
		/* We just released an l2, unhold the matching l1 */
		pd_entry_t *l0, tl0;
		vm_page_t l1pg;

		l0 = pmap_l0(pmap, va);
		tl0 = pmap_load(l0);
		l1pg = PHYS_TO_VM_PAGE(tl0 & ~ATTR_MASK);
		pmap_unwire_l3(pmap, va, l1pg, free);
	}
	pmap_invalidate_page(pmap, va);

	/*
	 * Put page on a list so that it is released after
	 * *ALL* TLB shootdown is done
	 */
	pmap_add_delayed_free_list(m, free, TRUE);
}