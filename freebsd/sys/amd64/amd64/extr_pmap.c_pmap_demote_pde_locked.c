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
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {scalar_t__ valid; scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DMAP_MAX_ADDRESS ; 
 scalar_t__ DMAP_MIN_ADDRESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ NPTEPG ; 
 int PG_MANAGED ; 
 int PG_PS ; 
 int PG_PS_FRAME ; 
 int PG_PTE_PROMOTE ; 
 int PG_U ; 
 int PG_W ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_ALLOC_INTERRUPT ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pde_store (int*,int) ; 
 int pmap_accessed_bit (int /*<<< orphan*/ ) ; 
 int pmap_cache_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_demote_pde_abort (int /*<<< orphan*/ ,scalar_t__,int*,int,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_demote_pde_check (int*,int) ; 
 int /*<<< orphan*/  pmap_fill_ptp (int*,int) ; 
 int pmap_global_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int pmap_modified_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pde_demotions ; 
 int /*<<< orphan*/  pmap_pde_pindex (scalar_t__) ; 
 int pmap_pku_mask_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pv_demote_pde (int /*<<< orphan*/ ,scalar_t__,int,struct rwlock**) ; 
 TYPE_1__* pmap_remove_pt_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_resident_count_inc (int /*<<< orphan*/ ,int) ; 
 int pmap_rw_bit (int /*<<< orphan*/ ) ; 
 int pmap_swap_pat (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_update_pde (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserve_pv_entries (int /*<<< orphan*/ ,scalar_t__,struct rwlock**) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vtopte (scalar_t__) ; 
 scalar_t__ workaround_erratum383 ; 

__attribute__((used)) static boolean_t
pmap_demote_pde_locked(pmap_t pmap, pd_entry_t *pde, vm_offset_t va,
    struct rwlock **lockp)
{
	pd_entry_t newpde, oldpde;
	pt_entry_t *firstpte, newpte;
	pt_entry_t PG_A, PG_G, PG_M, PG_PKU_MASK, PG_RW, PG_V;
	vm_paddr_t mptepa;
	vm_page_t mpte;
	int PG_PTE_CACHE;
	bool in_kernel;

	PG_A = pmap_accessed_bit(pmap);
	PG_G = pmap_global_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);
	PG_V = pmap_valid_bit(pmap);
	PG_PTE_CACHE = pmap_cache_mask(pmap, 0);
	PG_PKU_MASK = pmap_pku_mask_bit(pmap);

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	in_kernel = va >= VM_MAXUSER_ADDRESS;
	oldpde = *pde;
	KASSERT((oldpde & (PG_PS | PG_V)) == (PG_PS | PG_V),
	    ("pmap_demote_pde: oldpde is missing PG_PS and/or PG_V"));

	/*
	 * Invalidate the 2MB page mapping and return "failure" if the
	 * mapping was never accessed.
	 */
	if ((oldpde & PG_A) == 0) {
		KASSERT((oldpde & PG_W) == 0,
		    ("pmap_demote_pde: a wired mapping is missing PG_A"));
		pmap_demote_pde_abort(pmap, va, pde, oldpde, lockp);
		return (FALSE);
	}

	mpte = pmap_remove_pt_page(pmap, va);
	if (mpte == NULL) {
		KASSERT((oldpde & PG_W) == 0,
		    ("pmap_demote_pde: page table page for a wired mapping"
		    " is missing"));

		/*
		 * If the page table page is missing and the mapping
		 * is for a kernel address, the mapping must belong to
		 * the direct map.  Page table pages are preallocated
		 * for every other part of the kernel address space,
		 * so the direct map region is the only part of the
		 * kernel address space that must be handled here.
		 */
		KASSERT(!in_kernel || (va >= DMAP_MIN_ADDRESS &&
		    va < DMAP_MAX_ADDRESS),
		    ("pmap_demote_pde: No saved mpte for va %#lx", va));

		/*
		 * If the 2MB page mapping belongs to the direct map
		 * region of the kernel's address space, then the page
		 * allocation request specifies the highest possible
		 * priority (VM_ALLOC_INTERRUPT).  Otherwise, the
		 * priority is normal.
		 */
		mpte = vm_page_alloc(NULL, pmap_pde_pindex(va),
		    (in_kernel ? VM_ALLOC_INTERRUPT : VM_ALLOC_NORMAL) |
		    VM_ALLOC_NOOBJ | VM_ALLOC_WIRED);

		/*
		 * If the allocation of the new page table page fails,
		 * invalidate the 2MB page mapping and return "failure".
		 */
		if (mpte == NULL) {
			pmap_demote_pde_abort(pmap, va, pde, oldpde, lockp);
			return (FALSE);
		}

		if (!in_kernel) {
			mpte->ref_count = NPTEPG;
			pmap_resident_count_inc(pmap, 1);
		}
	}
	mptepa = VM_PAGE_TO_PHYS(mpte);
	firstpte = (pt_entry_t *)PHYS_TO_DMAP(mptepa);
	newpde = mptepa | PG_M | PG_A | (oldpde & PG_U) | PG_RW | PG_V;
	KASSERT((oldpde & (PG_M | PG_RW)) != PG_RW,
	    ("pmap_demote_pde: oldpde is missing PG_M"));
	newpte = oldpde & ~PG_PS;
	newpte = pmap_swap_pat(pmap, newpte);

	/*
	 * If the page table page is not leftover from an earlier promotion,
	 * initialize it.
	 */
	if (mpte->valid == 0)
		pmap_fill_ptp(firstpte, newpte);

	pmap_demote_pde_check(firstpte, newpte);

	/*
	 * If the mapping has changed attributes, update the page table
	 * entries.
	 */
	if ((*firstpte & PG_PTE_PROMOTE) != (newpte & PG_PTE_PROMOTE))
		pmap_fill_ptp(firstpte, newpte);

	/*
	 * The spare PV entries must be reserved prior to demoting the
	 * mapping, that is, prior to changing the PDE.  Otherwise, the state
	 * of the PDE and the PV lists will be inconsistent, which can result
	 * in reclaim_pv_chunk() attempting to remove a PV entry from the
	 * wrong PV list and pmap_pv_demote_pde() failing to find the expected
	 * PV entry for the 2MB page mapping that is being demoted.
	 */
	if ((oldpde & PG_MANAGED) != 0)
		reserve_pv_entries(pmap, NPTEPG - 1, lockp);

	/*
	 * Demote the mapping.  This pmap is locked.  The old PDE has
	 * PG_A set.  If the old PDE has PG_RW set, it also has PG_M
	 * set.  Thus, there is no danger of a race with another
	 * processor changing the setting of PG_A and/or PG_M between
	 * the read above and the store below. 
	 */
	if (workaround_erratum383)
		pmap_update_pde(pmap, va, pde, newpde);
	else
		pde_store(pde, newpde);

	/*
	 * Invalidate a stale recursive mapping of the page table page.
	 */
	if (in_kernel)
		pmap_invalidate_page(pmap, (vm_offset_t)vtopte(va));

	/*
	 * Demote the PV entry.
	 */
	if ((oldpde & PG_MANAGED) != 0)
		pmap_pv_demote_pde(pmap, va, oldpde & PG_PS_FRAME, lockp);

	atomic_add_long(&pmap_pde_demotions, 1);
	CTR2(KTR_PMAP, "pmap_demote_pde: success for va %#lx in pmap %p",
	    va, pmap);
	return (TRUE);
}