#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int u_int ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
typedef  TYPE_3__* pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_22__ {size_t wired_count; size_t resident_count; } ;
struct TYPE_24__ {TYPE_1__ pm_stats; } ;
struct TYPE_23__ {int ref_count; } ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 scalar_t__ ATTR_MASK ; 
 int ATTR_SW_DBM ; 
 int ATTR_SW_MANAGED ; 
 int ATTR_SW_WIRED ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_FAILURE ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int L2_BLOCK ; 
 size_t L2_SIZE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 TYPE_2__* PHYS_TO_VM_PAGE (scalar_t__) ; 
 int PMAP_ENTER_NOREPLACE ; 
 int PMAP_ENTER_NOSLEEP ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishst ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_2__* pmap_alloc_l2 (TYPE_3__*,scalar_t__,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_clear (int*) ; 
 scalar_t__ pmap_insert_pt_page (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pmap_invalidate_page (TYPE_3__*,scalar_t__) ; 
 int* pmap_l1 (TYPE_3__*,scalar_t__) ; 
 size_t pmap_l2_index (scalar_t__) ; 
 int /*<<< orphan*/  pmap_l2_mappings ; 
 scalar_t__ pmap_load (int*) ; 
 int /*<<< orphan*/  pmap_pv_insert_l2 (TYPE_3__*,scalar_t__,int,int,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_remove_l2 (TYPE_3__*,int*,scalar_t__,scalar_t__,struct spglist*,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_remove_l3_range (TYPE_3__*,int,scalar_t__,scalar_t__,struct spglist*,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_store (int*,int) ; 
 scalar_t__ pmap_unwire_l3 (TYPE_3__*,scalar_t__,TYPE_2__*,struct spglist*) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 

__attribute__((used)) static int
pmap_enter_l2(pmap_t pmap, vm_offset_t va, pd_entry_t new_l2, u_int flags,
    vm_page_t m, struct rwlock **lockp)
{
	struct spglist free;
	pd_entry_t *l2, old_l2;
	vm_page_t l2pg, mt;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);

	if ((l2pg = pmap_alloc_l2(pmap, va, (flags & PMAP_ENTER_NOSLEEP) != 0 ?
	    NULL : lockp)) == NULL) {
		CTR2(KTR_PMAP, "pmap_enter_l2: failure for va %#lx in pmap %p",
		    va, pmap);
		return (KERN_RESOURCE_SHORTAGE);
	}

	l2 = (pd_entry_t *)PHYS_TO_DMAP(VM_PAGE_TO_PHYS(l2pg));
	l2 = &l2[pmap_l2_index(va)];
	if ((old_l2 = pmap_load(l2)) != 0) {
		KASSERT(l2pg->ref_count > 1,
		    ("pmap_enter_l2: l2pg's ref count is too low"));
		if ((flags & PMAP_ENTER_NOREPLACE) != 0) {
			l2pg->ref_count--;
			CTR2(KTR_PMAP,
			    "pmap_enter_l2: failure for va %#lx in pmap %p",
			    va, pmap);
			return (KERN_FAILURE);
		}
		SLIST_INIT(&free);
		if ((old_l2 & ATTR_DESCR_MASK) == L2_BLOCK)
			(void)pmap_remove_l2(pmap, l2, va,
			    pmap_load(pmap_l1(pmap, va)), &free, lockp);
		else
			pmap_remove_l3_range(pmap, old_l2, va, va + L2_SIZE,
			    &free, lockp);
		vm_page_free_pages_toq(&free, true);
		if (va >= VM_MAXUSER_ADDRESS) {
			/*
			 * Both pmap_remove_l2() and pmap_remove_l3_range()
			 * will leave the kernel page table page zero filled.
			 * Nonetheless, the TLB could have an intermediate
			 * entry for the kernel page table page.
			 */
			mt = PHYS_TO_VM_PAGE(pmap_load(l2) & ~ATTR_MASK);
			if (pmap_insert_pt_page(pmap, mt, false))
				panic("pmap_enter_l2: trie insert failed");
			pmap_clear(l2);
			pmap_invalidate_page(pmap, va);
		} else
			KASSERT(pmap_load(l2) == 0,
			    ("pmap_enter_l2: non-zero L2 entry %p", l2));
	}

	if ((new_l2 & ATTR_SW_MANAGED) != 0) {
		/*
		 * Abort this mapping if its PV entry could not be created.
		 */
		if (!pmap_pv_insert_l2(pmap, va, new_l2, flags, lockp)) {
			SLIST_INIT(&free);
			if (pmap_unwire_l3(pmap, va, l2pg, &free)) {
				/*
				 * Although "va" is not mapped, the TLB could
				 * nonetheless have intermediate entries that
				 * refer to the freed page table pages.
				 * Invalidate those entries.
				 *
				 * XXX redundant invalidation (See
				 * _pmap_unwire_l3().)
				 */
				pmap_invalidate_page(pmap, va);
				vm_page_free_pages_toq(&free, true);
			}
			CTR2(KTR_PMAP,
			    "pmap_enter_l2: failure for va %#lx in pmap %p",
			    va, pmap);
			return (KERN_RESOURCE_SHORTAGE);
		}
		if ((new_l2 & ATTR_SW_DBM) != 0)
			for (mt = m; mt < &m[L2_SIZE / PAGE_SIZE]; mt++)
				vm_page_aflag_set(mt, PGA_WRITEABLE);
	}

	/*
	 * Increment counters.
	 */
	if ((new_l2 & ATTR_SW_WIRED) != 0)
		pmap->pm_stats.wired_count += L2_SIZE / PAGE_SIZE;
	pmap->pm_stats.resident_count += L2_SIZE / PAGE_SIZE;

	/*
	 * Map the superpage.
	 */
	pmap_store(l2, new_l2);
	dsb(ishst);

	atomic_add_long(&pmap_l2_mappings, 1);
	CTR2(KTR_PMAP, "pmap_enter_l2: success for va %#lx in pmap %p",
	    va, pmap);

	return (KERN_SUCCESS);
}