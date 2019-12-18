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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_6__ {scalar_t__ pindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ NUL1E ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pmap_add_delayed_free_list (TYPE_1__*,struct spglist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_distribute_l1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_l1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_l1_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_l2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_unwire_ptp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct spglist*) ; 
 int /*<<< orphan*/  vm_wire_sub (int) ; 

__attribute__((used)) static void
_pmap_unwire_ptp(pmap_t pmap, vm_offset_t va, vm_page_t m, struct spglist *free)
{
	vm_paddr_t phys;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	if (m->pindex >= NUL1E) {
		pd_entry_t *l1;
		l1 = pmap_l1(pmap, va);
		pmap_clear(l1);
		pmap_distribute_l1(pmap, pmap_l1_index(va), 0);
	} else {
		pd_entry_t *l2;
		l2 = pmap_l2(pmap, va);
		pmap_clear(l2);
	}
	pmap_resident_count_dec(pmap, 1);
	if (m->pindex < NUL1E) {
		pd_entry_t *l1;
		vm_page_t pdpg;

		l1 = pmap_l1(pmap, va);
		phys = PTE_TO_PHYS(pmap_load(l1));
		pdpg = PHYS_TO_VM_PAGE(phys);
		pmap_unwire_ptp(pmap, va, pdpg, free);
	}
	pmap_invalidate_page(pmap, va);

	vm_wire_sub(1);

	/* 
	 * Put page on a list so that it is released after
	 * *ALL* TLB shootdown is done
	 */
	pmap_add_delayed_free_list(m, free, TRUE);
}