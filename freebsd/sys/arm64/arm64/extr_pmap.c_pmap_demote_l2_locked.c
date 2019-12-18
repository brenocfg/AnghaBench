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
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_5__ {scalar_t__ valid; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int ATTR_AF ; 
 int ATTR_AP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_AP_RO ; 
 int ATTR_AP_RW_BIT ; 
 int ATTR_DESCR_MASK ; 
 int ATTR_MASK ; 
 int ATTR_SW_DBM ; 
 int ATTR_SW_MANAGED ; 
 int ATTR_SW_WIRED ; 
 int /*<<< orphan*/  CACHED_MEMORY ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int DMAP_TO_PHYS (scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int L2_BLOCK ; 
 scalar_t__ L2_OFFSET ; 
 scalar_t__ L2_SIZE ; 
 int L2_TABLE ; 
 int L3_OFFSET ; 
 int L3_PAGE ; 
 scalar_t__ Ln_ENTRIES ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NL3PG ; 
 scalar_t__ PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VIRT_IN_DMAP (scalar_t__) ; 
 int VM_ALLOC_INTERRUPT ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 scalar_t__ kva_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kva_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_demote_l2_abort (int /*<<< orphan*/ ,scalar_t__,int*,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_fill_l3 (int*,int) ; 
 int /*<<< orphan*/  pmap_kenter (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kremove (scalar_t__) ; 
 int /*<<< orphan*/  pmap_l2_demotions ; 
 int /*<<< orphan*/  pmap_l2_pindex (scalar_t__) ; 
 int pmap_load (int*) ; 
 int /*<<< orphan*/  pmap_pv_demote_l2 (int /*<<< orphan*/ ,scalar_t__,int,struct rwlock**) ; 
 TYPE_1__* pmap_remove_pt_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_resident_count_inc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_update_entry (int /*<<< orphan*/ ,int*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserve_pv_entries (int /*<<< orphan*/ ,scalar_t__,struct rwlock**) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static pt_entry_t *
pmap_demote_l2_locked(pmap_t pmap, pt_entry_t *l2, vm_offset_t va,
    struct rwlock **lockp)
{
	pt_entry_t *l3, newl3, oldl2;
	vm_offset_t tmpl2;
	vm_paddr_t l3phys;
	vm_page_t ml3;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	l3 = NULL;
	oldl2 = pmap_load(l2);
	KASSERT((oldl2 & ATTR_DESCR_MASK) == L2_BLOCK,
	    ("pmap_demote_l2: Demoting a non-block entry"));
	va &= ~L2_OFFSET;

	tmpl2 = 0;
	if (va <= (vm_offset_t)l2 && va + L2_SIZE > (vm_offset_t)l2) {
		tmpl2 = kva_alloc(PAGE_SIZE);
		if (tmpl2 == 0)
			return (NULL);
	}

	/*
	 * Invalidate the 2MB page mapping and return "failure" if the
	 * mapping was never accessed.
	 */
	if ((oldl2 & ATTR_AF) == 0) {
		KASSERT((oldl2 & ATTR_SW_WIRED) == 0,
		    ("pmap_demote_l2: a wired mapping is missing ATTR_AF"));
		pmap_demote_l2_abort(pmap, va, l2, lockp);
		CTR2(KTR_PMAP, "pmap_demote_l2: failure for va %#lx in pmap %p",
		    va, pmap);
		goto fail;
	}

	if ((ml3 = pmap_remove_pt_page(pmap, va)) == NULL) {
		KASSERT((oldl2 & ATTR_SW_WIRED) == 0,
		    ("pmap_demote_l2: page table page for a wired mapping"
		    " is missing"));

		/*
		 * If the page table page is missing and the mapping
		 * is for a kernel address, the mapping must belong to
		 * the direct map.  Page table pages are preallocated
		 * for every other part of the kernel address space,
		 * so the direct map region is the only part of the
		 * kernel address space that must be handled here.
		 */
		KASSERT(va < VM_MAXUSER_ADDRESS || VIRT_IN_DMAP(va),
		    ("pmap_demote_l2: No saved mpte for va %#lx", va));

		/*
		 * If the 2MB page mapping belongs to the direct map
		 * region of the kernel's address space, then the page
		 * allocation request specifies the highest possible
		 * priority (VM_ALLOC_INTERRUPT).  Otherwise, the
		 * priority is normal.
		 */
		ml3 = vm_page_alloc(NULL, pmap_l2_pindex(va),
		    (VIRT_IN_DMAP(va) ? VM_ALLOC_INTERRUPT : VM_ALLOC_NORMAL) |
		    VM_ALLOC_NOOBJ | VM_ALLOC_WIRED);

		/*
		 * If the allocation of the new page table page fails,
		 * invalidate the 2MB page mapping and return "failure".
		 */
		if (ml3 == NULL) {
			pmap_demote_l2_abort(pmap, va, l2, lockp);
			CTR2(KTR_PMAP, "pmap_demote_l2: failure for va %#lx"
			    " in pmap %p", va, pmap);
			goto fail;
		}

		if (va < VM_MAXUSER_ADDRESS) {
			ml3->ref_count = NL3PG;
			pmap_resident_count_inc(pmap, 1);
		}
	}
	l3phys = VM_PAGE_TO_PHYS(ml3);
	l3 = (pt_entry_t *)PHYS_TO_DMAP(l3phys);
	newl3 = (oldl2 & ~ATTR_DESCR_MASK) | L3_PAGE;
	KASSERT((oldl2 & (ATTR_AP_RW_BIT | ATTR_SW_DBM)) !=
	    (ATTR_AP(ATTR_AP_RO) | ATTR_SW_DBM),
	    ("pmap_demote_l2: L2 entry is writeable but not dirty"));

	/*
	 * If the page table page is not leftover from an earlier promotion,
	 * or the mapping attributes have changed, (re)initialize the L3 table.
	 *
	 * When pmap_update_entry() clears the old L2 mapping, it (indirectly)
	 * performs a dsb().  That dsb() ensures that the stores for filling
	 * "l3" are visible before "l3" is added to the page table.
	 */
	if (ml3->valid == 0 || (l3[0] & ATTR_MASK) != (newl3 & ATTR_MASK))
		pmap_fill_l3(l3, newl3);

	/*
	 * Map the temporary page so we don't lose access to the l2 table.
	 */
	if (tmpl2 != 0) {
		pmap_kenter(tmpl2, PAGE_SIZE,
		    DMAP_TO_PHYS((vm_offset_t)l2) & ~L3_OFFSET, CACHED_MEMORY);
		l2 = (pt_entry_t *)(tmpl2 + ((vm_offset_t)l2 & PAGE_MASK));
	}

	/*
	 * The spare PV entries must be reserved prior to demoting the
	 * mapping, that is, prior to changing the PDE.  Otherwise, the state
	 * of the L2 and the PV lists will be inconsistent, which can result
	 * in reclaim_pv_chunk() attempting to remove a PV entry from the
	 * wrong PV list and pmap_pv_demote_l2() failing to find the expected
	 * PV entry for the 2MB page mapping that is being demoted.
	 */
	if ((oldl2 & ATTR_SW_MANAGED) != 0)
		reserve_pv_entries(pmap, Ln_ENTRIES - 1, lockp);

	/*
	 * Pass PAGE_SIZE so that a single TLB invalidation is performed on
	 * the 2MB page mapping.
	 */
	pmap_update_entry(pmap, l2, l3phys | L2_TABLE, va, PAGE_SIZE);

	/*
	 * Demote the PV entry.
	 */
	if ((oldl2 & ATTR_SW_MANAGED) != 0)
		pmap_pv_demote_l2(pmap, va, oldl2 & ~ATTR_MASK, lockp);

	atomic_add_long(&pmap_l2_demotions, 1);
	CTR3(KTR_PMAP, "pmap_demote_l2: success for va %#lx"
	    " in pmap %p %lx", va, pmap, l3[0]);

fail:
	if (tmpl2 != 0) {
		pmap_kremove(tmpl2);
		kva_free(tmpl2, PAGE_SIZE);
	}

	return (l3);

}