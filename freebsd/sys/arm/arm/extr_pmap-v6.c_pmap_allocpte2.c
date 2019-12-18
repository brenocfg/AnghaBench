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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  pt1_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pm_pt1; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int PMAP_ENTER_NOSLEEP ; 
 int /*<<< orphan*/ * _pmap_allocpte2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_demote_pte1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt2_wirecount_inc (int /*<<< orphan*/ *,int) ; 
 int pte1_index (int /*<<< orphan*/ ) ; 
 scalar_t__ pte1_is_link (int /*<<< orphan*/ ) ; 
 scalar_t__ pte1_is_section (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_link_pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
pmap_allocpte2(pmap_t pmap, vm_offset_t va, u_int flags)
{
	u_int pte1_idx;
	pt1_entry_t *pte1p, pte1;
	vm_page_t m;

	pte1_idx = pte1_index(va);
retry:
	pte1p = pmap->pm_pt1 + pte1_idx;
	pte1 = pte1_load(pte1p);

	/*
	 * This supports switching from a 1MB page to a
	 * normal 4K page.
	 */
	if (pte1_is_section(pte1)) {
		(void)pmap_demote_pte1(pmap, pte1p, va);
		/*
		 * Reload pte1 after demotion.
		 *
		 * Note: Demotion can even fail as either PT2 is not find for
		 *       the virtual address or PT2PG can not be allocated.
		 */
		pte1 = pte1_load(pte1p);
	}

	/*
	 * If the L2 page table page is mapped, we just increment the
	 * hold count, and activate it.
	 */
	if (pte1_is_link(pte1)) {
		m = PHYS_TO_VM_PAGE(pte1_link_pa(pte1));
		pt2_wirecount_inc(m, pte1_idx);
	} else  {
		/*
		 * Here if the PT2 isn't mapped, or if it has
		 * been deallocated.
		 */
		m = _pmap_allocpte2(pmap, va, flags);
		if (m == NULL && (flags & PMAP_ENTER_NOSLEEP) == 0)
			goto retry;
	}

	return (m);
}