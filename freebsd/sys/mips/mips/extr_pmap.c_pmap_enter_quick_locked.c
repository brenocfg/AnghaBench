#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_18__ ;
typedef  struct TYPE_25__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pt_entry_t ;
typedef  TYPE_4__* pmap_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_27__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_30__ {TYPE_1__ pm_stats; } ;
struct TYPE_29__ {int oflags; unsigned int pindex; int /*<<< orphan*/  ref_count; } ;
struct TYPE_28__ {TYPE_4__ vm_pmap; } ;
struct TYPE_26__ {TYPE_2__* p_vmspace; } ;
struct TYPE_25__ {int /*<<< orphan*/  clean_eva; int /*<<< orphan*/  clean_sva; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MIPS_DIRECT_TO_PHYS (scalar_t__) ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_3__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_ENTER_NOSLEEP ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_PTE_SET_CACHE_BITS (int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int PTE_G ; 
 int PTE_MANAGED ; 
 int PTE_RO ; 
 int PTE_V ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int TLBLO_PA_TO_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_3__*) ; 
 int VPO_UNMANAGED ; 
 TYPE_3__* _pmap_allocpte (TYPE_4__*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_18__* curproc ; 
 scalar_t__ is_kernel_pmap (TYPE_4__*) ; 
 TYPE_16__ kmi ; 
 int /*<<< orphan*/  mips_dcache_wbinv_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_icache_sync_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* pmap_pde (TYPE_4__*,int /*<<< orphan*/ ) ; 
 unsigned int pmap_pde_pindex (int /*<<< orphan*/ ) ; 
 int* pmap_pte (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_try_insert_pv_entry (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  pmap_unwire_ptp (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ pte_test (int*,int) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_page_t
pmap_enter_quick_locked(pmap_t pmap, vm_offset_t va, vm_page_t m,
    vm_prot_t prot, vm_page_t mpte)
{
	pt_entry_t *pte, npte;
	vm_paddr_t pa;

	KASSERT(va < kmi.clean_sva || va >= kmi.clean_eva ||
	    (m->oflags & VPO_UNMANAGED) != 0,
	    ("pmap_enter_quick_locked: managed mapping within the clean submap"));
	rw_assert(&pvh_global_lock, RA_WLOCKED);
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);

	/*
	 * In the case that a page table page is not resident, we are
	 * creating it here.
	 */
	if (va < VM_MAXUSER_ADDRESS) {
		pd_entry_t *pde;
		unsigned ptepindex;

		/*
		 * Calculate pagetable page index
		 */
		ptepindex = pmap_pde_pindex(va);
		if (mpte && (mpte->pindex == ptepindex)) {
			mpte->ref_count++;
		} else {
			/*
			 * Get the page directory entry
			 */
			pde = pmap_pde(pmap, va);

			/*
			 * If the page table page is mapped, we just
			 * increment the hold count, and activate it.
			 */
			if (pde && *pde != 0) {
				mpte = PHYS_TO_VM_PAGE(
				    MIPS_DIRECT_TO_PHYS(*pde));
				mpte->ref_count++;
			} else {
				mpte = _pmap_allocpte(pmap, ptepindex,
				    PMAP_ENTER_NOSLEEP);
				if (mpte == NULL)
					return (mpte);
			}
		}
	} else {
		mpte = NULL;
	}

	pte = pmap_pte(pmap, va);
	if (pte_test(pte, PTE_V)) {
		if (mpte != NULL) {
			mpte->ref_count--;
			mpte = NULL;
		}
		return (mpte);
	}

	/*
	 * Enter on the PV list if part of our managed memory.
	 */
	if ((m->oflags & VPO_UNMANAGED) == 0 &&
	    !pmap_try_insert_pv_entry(pmap, mpte, va, m)) {
		if (mpte != NULL) {
			pmap_unwire_ptp(pmap, va, mpte);
			mpte = NULL;
		}
		return (mpte);
	}

	/*
	 * Increment counters
	 */
	pmap->pm_stats.resident_count++;

	pa = VM_PAGE_TO_PHYS(m);

	/*
	 * Now validate mapping with RO protection
	 */
	npte = PTE_RO | TLBLO_PA_TO_PFN(pa) | PTE_V;
	if ((m->oflags & VPO_UNMANAGED) == 0)
		npte |= PTE_MANAGED;

	PMAP_PTE_SET_CACHE_BITS(npte, pa, m);

	if (is_kernel_pmap(pmap))
		*pte = npte | PTE_G;
	else {
		*pte = npte;
		/*
		 * Sync I & D caches.  Do this only if the target pmap
		 * belongs to the current process.  Otherwise, an
		 * unresolvable TLB miss may occur. */
		if (pmap == &curproc->p_vmspace->vm_pmap) {
			va &= ~PAGE_MASK;
			mips_icache_sync_range(va, PAGE_SIZE);
			mips_dcache_wbinv_range(va, PAGE_SIZE);
		}
	}
	return (mpte);
}