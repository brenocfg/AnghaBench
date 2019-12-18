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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_TO_PHYS (scalar_t__) ; 
 TYPE_1__* _pmap_alloc_l3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rwlock**) ; 
 int /*<<< orphan*/ * pmap_l2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_l2_pindex (int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
pmap_alloc_l3(pmap_t pmap, vm_offset_t va, struct rwlock **lockp)
{
	vm_pindex_t ptepindex;
	pd_entry_t *l2;
	vm_paddr_t phys;
	vm_page_t m;

	/*
	 * Calculate pagetable page index
	 */
	ptepindex = pmap_l2_pindex(va);
retry:
	/*
	 * Get the page directory entry
	 */
	l2 = pmap_l2(pmap, va);

	/*
	 * If the page table page is mapped, we just increment the
	 * hold count, and activate it.
	 */
	if (l2 != NULL && pmap_load(l2) != 0) {
		phys = PTE_TO_PHYS(pmap_load(l2));
		m = PHYS_TO_VM_PAGE(phys);
		m->ref_count++;
	} else {
		/*
		 * Here if the pte page isn't mapped, or if it has been
		 * deallocated.
		 */
		m = _pmap_alloc_l3(pmap, ptepindex, lockp);
		if (m == NULL && lockp != NULL)
			goto retry;
	}
	return (m);
}