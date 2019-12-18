#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_4__ ;
typedef  struct TYPE_49__   TYPE_3__ ;
typedef  struct TYPE_48__   TYPE_30__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_29__ ;
typedef  struct TYPE_45__   TYPE_1__ ;
typedef  struct TYPE_44__   TYPE_13__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int u_int ;
struct rwlock {int dummy; } ;
typedef  TYPE_3__* pv_entry_t ;
typedef  int pt_entry_t ;
typedef  TYPE_4__* pmap_t ;
typedef  int pd_entry_t ;
typedef  scalar_t__ int8_t ;
typedef  int boolean_t ;
struct TYPE_45__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_50__ {scalar_t__ pm_type; TYPE_1__ pm_stats; } ;
struct TYPE_49__ {int pv_va; } ;
struct TYPE_48__ {int clean_sva; int clean_eva; } ;
struct TYPE_44__ {int /*<<< orphan*/  pv_gen; int /*<<< orphan*/  pv_list; int /*<<< orphan*/  pat_mode; } ;
struct TYPE_47__ {int oflags; scalar_t__ psind; scalar_t__ ref_count; int aflags; int flags; TYPE_13__ md; } ;
struct TYPE_46__ {int /*<<< orphan*/  pv_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_PV_LIST_LOCK_TO_PHYS (struct rwlock**,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 scalar_t__ NPTEPG ; 
 int PDRMASK ; 
 int PGA_REFERENCED ; 
 int PGA_WRITEABLE ; 
 int PG_FICTITIOUS ; 
 int PG_FRAME ; 
 int PG_MANAGED ; 
 int PG_NX ; 
 int PG_PS ; 
 int PG_U ; 
 int PG_W ; 
 TYPE_2__* PHYS_TO_VM_PAGE (int) ; 
 int PMAP_ENTER_NOSLEEP ; 
 int PMAP_ENTER_RESERVED ; 
 int PMAP_ENTER_WIRED ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_4__*) ; 
 scalar_t__ PT_X86 ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int UPT_MAX_ADDRESS ; 
 int UPT_MIN_ADDRESS ; 
 int VM_MAXUSER_ADDRESS ; 
 int VM_MAX_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  VM_PAGE_OBJECT_BUSY_ASSERT (TYPE_2__*) ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_WRITE ; 
 int VPO_UNMANAGED ; 
 TYPE_2__* _pmap_allocpte (TYPE_4__*,int /*<<< orphan*/ ,struct rwlock**) ; 
 int /*<<< orphan*/  free_pv_entry (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* get_pv_entry (TYPE_4__*,struct rwlock**) ; 
 TYPE_4__* kernel_pmap ; 
 TYPE_30__ kmi ; 
 TYPE_29__* pa_to_pvh (int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int pg_nx ; 
 int pmap_accessed_bit (TYPE_4__*) ; 
 int pmap_cache_bits (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmap_demote_pde_locked (TYPE_4__*,int*,int,struct rwlock**) ; 
 int pmap_enter_pde (TYPE_4__*,int,int,int,TYPE_2__*,struct rwlock**) ; 
 int pmap_global_bit (TYPE_4__*) ; 
 int /*<<< orphan*/  pmap_invalidate_page (TYPE_4__*,int) ; 
 int pmap_modified_bit (TYPE_4__*) ; 
 int* pmap_pde (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_pde_pindex (int) ; 
 int* pmap_pde_to_pte (int*,int) ; 
 int pmap_pkru_get (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_promote_pde (TYPE_4__*,int*,int,struct rwlock**) ; 
 scalar_t__ pmap_ps_enabled (TYPE_4__*) ; 
 TYPE_3__* pmap_pvh_remove (TYPE_13__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_resident_count_inc (TYPE_4__*,int) ; 
 int pmap_rw_bit (TYPE_4__*) ; 
 int pmap_valid_bit (TYPE_4__*) ; 
 int pte_load_clear (int*) ; 
 int pte_load_store (int*,int) ; 
 int /*<<< orphan*/  pte_store (int*,int) ; 
 int /*<<< orphan*/  pv_next ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 
 int trunc_page (int) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_2__*) ; 
 scalar_t__ vm_reserv_level_iffullpop (TYPE_2__*) ; 

int
pmap_enter(pmap_t pmap, vm_offset_t va, vm_page_t m, vm_prot_t prot,
    u_int flags, int8_t psind)
{
	struct rwlock *lock;
	pd_entry_t *pde;
	pt_entry_t *pte, PG_G, PG_A, PG_M, PG_RW, PG_V;
	pt_entry_t newpte, origpte;
	pv_entry_t pv;
	vm_paddr_t opa, pa;
	vm_page_t mpte, om;
	int rv;
	boolean_t nosleep;

	PG_A = pmap_accessed_bit(pmap);
	PG_G = pmap_global_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_V = pmap_valid_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);

	va = trunc_page(va);
	KASSERT(va <= VM_MAX_KERNEL_ADDRESS, ("pmap_enter: toobig"));
	KASSERT(va < UPT_MIN_ADDRESS || va >= UPT_MAX_ADDRESS,
	    ("pmap_enter: invalid to pmap_enter page table pages (va: 0x%lx)",
	    va));
	KASSERT((m->oflags & VPO_UNMANAGED) != 0 || va < kmi.clean_sva ||
	    va >= kmi.clean_eva,
	    ("pmap_enter: managed mapping within the clean submap"));
	if ((m->oflags & VPO_UNMANAGED) == 0)
		VM_PAGE_OBJECT_BUSY_ASSERT(m);
	KASSERT((flags & PMAP_ENTER_RESERVED) == 0,
	    ("pmap_enter: flags %u has reserved bits set", flags));
	pa = VM_PAGE_TO_PHYS(m);
	newpte = (pt_entry_t)(pa | PG_A | PG_V);
	if ((flags & VM_PROT_WRITE) != 0)
		newpte |= PG_M;
	if ((prot & VM_PROT_WRITE) != 0)
		newpte |= PG_RW;
	KASSERT((newpte & (PG_M | PG_RW)) != PG_M,
	    ("pmap_enter: flags includes VM_PROT_WRITE but prot doesn't"));
	if ((prot & VM_PROT_EXECUTE) == 0)
		newpte |= pg_nx;
	if ((flags & PMAP_ENTER_WIRED) != 0)
		newpte |= PG_W;
	if (va < VM_MAXUSER_ADDRESS)
		newpte |= PG_U;
	if (pmap == kernel_pmap)
		newpte |= PG_G;
	newpte |= pmap_cache_bits(pmap, m->md.pat_mode, psind > 0);

	/*
	 * Set modified bit gratuitously for writeable mappings if
	 * the page is unmanaged. We do not want to take a fault
	 * to do the dirty bit accounting for these mappings.
	 */
	if ((m->oflags & VPO_UNMANAGED) != 0) {
		if ((newpte & PG_RW) != 0)
			newpte |= PG_M;
	} else
		newpte |= PG_MANAGED;

	lock = NULL;
	PMAP_LOCK(pmap);
	if (psind == 1) {
		/* Assert the required virtual and physical alignment. */ 
		KASSERT((va & PDRMASK) == 0, ("pmap_enter: va unaligned"));
		KASSERT(m->psind > 0, ("pmap_enter: m->psind < psind"));
		rv = pmap_enter_pde(pmap, va, newpte | PG_PS, flags, m, &lock);
		goto out;
	}
	mpte = NULL;

	/*
	 * In the case that a page table page is not
	 * resident, we are creating it here.
	 */
retry:
	pde = pmap_pde(pmap, va);
	if (pde != NULL && (*pde & PG_V) != 0 && ((*pde & PG_PS) == 0 ||
	    pmap_demote_pde_locked(pmap, pde, va, &lock))) {
		pte = pmap_pde_to_pte(pde, va);
		if (va < VM_MAXUSER_ADDRESS && mpte == NULL) {
			mpte = PHYS_TO_VM_PAGE(*pde & PG_FRAME);
			mpte->ref_count++;
		}
	} else if (va < VM_MAXUSER_ADDRESS) {
		/*
		 * Here if the pte page isn't mapped, or if it has been
		 * deallocated.
		 */
		nosleep = (flags & PMAP_ENTER_NOSLEEP) != 0;
		mpte = _pmap_allocpte(pmap, pmap_pde_pindex(va),
		    nosleep ? NULL : &lock);
		if (mpte == NULL && nosleep) {
			rv = KERN_RESOURCE_SHORTAGE;
			goto out;
		}
		goto retry;
	} else
		panic("pmap_enter: invalid page directory va=%#lx", va);

	origpte = *pte;
	pv = NULL;
	if (va < VM_MAXUSER_ADDRESS && pmap->pm_type == PT_X86)
		newpte |= pmap_pkru_get(pmap, va);

	/*
	 * Is the specified virtual address already mapped?
	 */
	if ((origpte & PG_V) != 0) {
		/*
		 * Wiring change, just update stats. We don't worry about
		 * wiring PT pages as they remain resident as long as there
		 * are valid mappings in them. Hence, if a user page is wired,
		 * the PT page will be also.
		 */
		if ((newpte & PG_W) != 0 && (origpte & PG_W) == 0)
			pmap->pm_stats.wired_count++;
		else if ((newpte & PG_W) == 0 && (origpte & PG_W) != 0)
			pmap->pm_stats.wired_count--;

		/*
		 * Remove the extra PT page reference.
		 */
		if (mpte != NULL) {
			mpte->ref_count--;
			KASSERT(mpte->ref_count > 0,
			    ("pmap_enter: missing reference to page table page,"
			     " va: 0x%lx", va));
		}

		/*
		 * Has the physical page changed?
		 */
		opa = origpte & PG_FRAME;
		if (opa == pa) {
			/*
			 * No, might be a protection or wiring change.
			 */
			if ((origpte & PG_MANAGED) != 0 &&
			    (newpte & PG_RW) != 0)
				vm_page_aflag_set(m, PGA_WRITEABLE);
			if (((origpte ^ newpte) & ~(PG_M | PG_A)) == 0)
				goto unchanged;
			goto validate;
		}

		/*
		 * The physical page has changed.  Temporarily invalidate
		 * the mapping.  This ensures that all threads sharing the
		 * pmap keep a consistent view of the mapping, which is
		 * necessary for the correct handling of COW faults.  It
		 * also permits reuse of the old mapping's PV entry,
		 * avoiding an allocation.
		 *
		 * For consistency, handle unmanaged mappings the same way.
		 */
		origpte = pte_load_clear(pte);
		KASSERT((origpte & PG_FRAME) == opa,
		    ("pmap_enter: unexpected pa update for %#lx", va));
		if ((origpte & PG_MANAGED) != 0) {
			om = PHYS_TO_VM_PAGE(opa);

			/*
			 * The pmap lock is sufficient to synchronize with
			 * concurrent calls to pmap_page_test_mappings() and
			 * pmap_ts_referenced().
			 */
			if ((origpte & (PG_M | PG_RW)) == (PG_M | PG_RW))
				vm_page_dirty(om);
			if ((origpte & PG_A) != 0)
				vm_page_aflag_set(om, PGA_REFERENCED);
			CHANGE_PV_LIST_LOCK_TO_PHYS(&lock, opa);
			pv = pmap_pvh_remove(&om->md, pmap, va);
			KASSERT(pv != NULL,
			    ("pmap_enter: no PV entry for %#lx", va));
			if ((newpte & PG_MANAGED) == 0)
				free_pv_entry(pmap, pv);
			if ((om->aflags & PGA_WRITEABLE) != 0 &&
			    TAILQ_EMPTY(&om->md.pv_list) &&
			    ((om->flags & PG_FICTITIOUS) != 0 ||
			    TAILQ_EMPTY(&pa_to_pvh(opa)->pv_list)))
				vm_page_aflag_clear(om, PGA_WRITEABLE);
		}
		if ((origpte & PG_A) != 0)
			pmap_invalidate_page(pmap, va);
		origpte = 0;
	} else {
		/*
		 * Increment the counters.
		 */
		if ((newpte & PG_W) != 0)
			pmap->pm_stats.wired_count++;
		pmap_resident_count_inc(pmap, 1);
	}

	/*
	 * Enter on the PV list if part of our managed memory.
	 */
	if ((newpte & PG_MANAGED) != 0) {
		if (pv == NULL) {
			pv = get_pv_entry(pmap, &lock);
			pv->pv_va = va;
		}
		CHANGE_PV_LIST_LOCK_TO_PHYS(&lock, pa);
		TAILQ_INSERT_TAIL(&m->md.pv_list, pv, pv_next);
		m->md.pv_gen++;
		if ((newpte & PG_RW) != 0)
			vm_page_aflag_set(m, PGA_WRITEABLE);
	}

	/*
	 * Update the PTE.
	 */
	if ((origpte & PG_V) != 0) {
validate:
		origpte = pte_load_store(pte, newpte);
		KASSERT((origpte & PG_FRAME) == pa,
		    ("pmap_enter: unexpected pa update for %#lx", va));
		if ((newpte & PG_M) == 0 && (origpte & (PG_M | PG_RW)) ==
		    (PG_M | PG_RW)) {
			if ((origpte & PG_MANAGED) != 0)
				vm_page_dirty(m);

			/*
			 * Although the PTE may still have PG_RW set, TLB
			 * invalidation may nonetheless be required because
			 * the PTE no longer has PG_M set.
			 */
		} else if ((origpte & PG_NX) != 0 || (newpte & PG_NX) == 0) {
			/*
			 * This PTE change does not require TLB invalidation.
			 */
			goto unchanged;
		}
		if ((origpte & PG_A) != 0)
			pmap_invalidate_page(pmap, va);
	} else
		pte_store(pte, newpte);

unchanged:

#if VM_NRESERVLEVEL > 0
	/*
	 * If both the page table page and the reservation are fully
	 * populated, then attempt promotion.
	 */
	if ((mpte == NULL || mpte->ref_count == NPTEPG) &&
	    pmap_ps_enabled(pmap) &&
	    (m->flags & PG_FICTITIOUS) == 0 &&
	    vm_reserv_level_iffullpop(m) == 0)
		pmap_promote_pde(pmap, pde, va, &lock);
#endif

	rv = KERN_SUCCESS;
out:
	if (lock != NULL)
		rw_wunlock(lock);
	PMAP_UNLOCK(pmap);
	return (rv);
}