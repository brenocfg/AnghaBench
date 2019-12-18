#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
struct md_page {int /*<<< orphan*/  pv_list; } ;
typedef  int pt_entry_t ;
typedef  TYPE_4__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_20__ {int wired_count; } ;
struct TYPE_23__ {TYPE_1__ pm_stats; } ;
struct TYPE_21__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_22__ {scalar_t__ valid; scalar_t__ ref_count; TYPE_2__ md; } ;

/* Variables and functions */
 int ATTR_AF ; 
 int ATTR_DESCR_MASK ; 
 int ATTR_MASK ; 
 int ATTR_SW_MANAGED ; 
 int ATTR_SW_WIRED ; 
 int /*<<< orphan*/  CHANGE_PV_LIST_LOCK_TO_PHYS (struct rwlock**,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L2_BLOCK ; 
 int L2_OFFSET ; 
 int L2_SIZE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ NL3PG ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 TYPE_3__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 TYPE_4__* kernel_pmap ; 
 struct md_page* pa_to_pvh (int) ; 
 int /*<<< orphan*/  pmap_add_delayed_free_list (TYPE_3__*,struct spglist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_page (TYPE_4__*,int) ; 
 int pmap_load_clear (int*) ; 
 scalar_t__ pmap_pte_dirty (int) ; 
 int /*<<< orphan*/  pmap_pvh_free (struct md_page*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_remove_kernel_l2 (TYPE_4__*,int*,int) ; 
 TYPE_3__* pmap_remove_pt_page (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (TYPE_4__*,int) ; 
 int pmap_unuse_pt (TYPE_4__*,int,int /*<<< orphan*/ ,struct spglist*) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_3__*) ; 

__attribute__((used)) static int
pmap_remove_l2(pmap_t pmap, pt_entry_t *l2, vm_offset_t sva,
    pd_entry_t l1e, struct spglist *free, struct rwlock **lockp)
{
	struct md_page *pvh;
	pt_entry_t old_l2;
	vm_offset_t eva, va;
	vm_page_t m, ml3;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	KASSERT((sva & L2_OFFSET) == 0, ("pmap_remove_l2: sva is not aligned"));
	old_l2 = pmap_load_clear(l2);
	KASSERT((old_l2 & ATTR_DESCR_MASK) == L2_BLOCK,
	    ("pmap_remove_l2: L2e %lx is not a block mapping", old_l2));

	/*
	 * Since a promotion must break the 4KB page mappings before making
	 * the 2MB page mapping, a pmap_invalidate_page() suffices.
	 */
	pmap_invalidate_page(pmap, sva);

	if (old_l2 & ATTR_SW_WIRED)
		pmap->pm_stats.wired_count -= L2_SIZE / PAGE_SIZE;
	pmap_resident_count_dec(pmap, L2_SIZE / PAGE_SIZE);
	if (old_l2 & ATTR_SW_MANAGED) {
		CHANGE_PV_LIST_LOCK_TO_PHYS(lockp, old_l2 & ~ATTR_MASK);
		pvh = pa_to_pvh(old_l2 & ~ATTR_MASK);
		pmap_pvh_free(pvh, pmap, sva);
		eva = sva + L2_SIZE;
		for (va = sva, m = PHYS_TO_VM_PAGE(old_l2 & ~ATTR_MASK);
		    va < eva; va += PAGE_SIZE, m++) {
			if (pmap_pte_dirty(old_l2))
				vm_page_dirty(m);
			if (old_l2 & ATTR_AF)
				vm_page_aflag_set(m, PGA_REFERENCED);
			if (TAILQ_EMPTY(&m->md.pv_list) &&
			    TAILQ_EMPTY(&pvh->pv_list))
				vm_page_aflag_clear(m, PGA_WRITEABLE);
		}
	}
	if (pmap == kernel_pmap) {
		pmap_remove_kernel_l2(pmap, l2, sva);
	} else {
		ml3 = pmap_remove_pt_page(pmap, sva);
		if (ml3 != NULL) {
			KASSERT(ml3->valid == VM_PAGE_BITS_ALL,
			    ("pmap_remove_l2: l3 page not promoted"));
			pmap_resident_count_dec(pmap, 1);
			KASSERT(ml3->ref_count == NL3PG,
			    ("pmap_remove_l2: l3 page ref count error"));
			ml3->ref_count = 0;
			pmap_add_delayed_free_list(ml3, free, FALSE);
		}
	}
	return (pmap_unuse_pt(pmap, sva, l1e, free));
}