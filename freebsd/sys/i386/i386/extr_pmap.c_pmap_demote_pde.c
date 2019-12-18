#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
struct spglist {int dummy; } ;
typedef  int pt_entry_t ;
typedef  TYPE_3__* pmap_t ;
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_19__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_21__ {TYPE_1__ pm_stats; } ;
struct TYPE_20__ {scalar_t__ valid; int /*<<< orphan*/  ref_count; } ;
struct TYPE_18__ {scalar_t__ td_pinned; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int* KPTmap ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NPTEPG ; 
 int* PADDR1 ; 
 int* PADDR2 ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int PDRSHIFT ; 
 int PG_A ; 
 int PG_FRAME ; 
 int PG_G ; 
 int PG_M ; 
 int PG_MANAGED ; 
 int PG_PDE_PAT ; 
 int PG_PS ; 
 int PG_PS_FRAME ; 
 int PG_PTE_PAT ; 
 int PG_PTE_PROMOTE ; 
 int PG_RW ; 
 int PG_U ; 
 int PG_V ; 
 int PG_W ; 
 int* PMAP1 ; 
 int /*<<< orphan*/  PMAP1changed ; 
 int /*<<< orphan*/  PMAP1changedcpu ; 
 scalar_t__ PMAP1cpu ; 
 int /*<<< orphan*/  PMAP1unchanged ; 
 int* PMAP2 ; 
 int /*<<< orphan*/  PMAP2mutex ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  cpuid ; 
 TYPE_14__* curthread ; 
 size_t i386_btop (int) ; 
 int /*<<< orphan*/  invlcaddr (int*) ; 
 TYPE_3__* kernel_pmap ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pde_store (int*,int) ; 
 int /*<<< orphan*/  pmap_fill_ptp (int*,int) ; 
 int /*<<< orphan*/  pmap_invalidate_page_int (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pmap_invalidate_pde_page (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  pmap_kenter_pde (int,int) ; 
 int /*<<< orphan*/  pmap_pde_demotions ; 
 int /*<<< orphan*/  pmap_pv_demote_pde (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  pmap_remove_pde (TYPE_3__*,int*,int,struct spglist*) ; 
 TYPE_2__* pmap_remove_pt_page (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pmap_update_pde (TYPE_3__*,int,int*,int) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 scalar_t__ rw_wowned (int /*<<< orphan*/ *) ; 
 int trunc_4mpage (int) ; 
 TYPE_2__* vm_page_alloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 
 scalar_t__ vtopte (int) ; 
 scalar_t__ workaround_erratum383 ; 

__attribute__((used)) static boolean_t
pmap_demote_pde(pmap_t pmap, pd_entry_t *pde, vm_offset_t va)
{
	pd_entry_t newpde, oldpde;
	pt_entry_t *firstpte, newpte;
	vm_paddr_t mptepa;
	vm_page_t mpte;
	struct spglist free;
	vm_offset_t sva;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	oldpde = *pde;
	KASSERT((oldpde & (PG_PS | PG_V)) == (PG_PS | PG_V),
	    ("pmap_demote_pde: oldpde is missing PG_PS and/or PG_V"));
	if ((oldpde & PG_A) == 0 || (mpte = pmap_remove_pt_page(pmap, va)) ==
	    NULL) {
		KASSERT((oldpde & PG_W) == 0,
		    ("pmap_demote_pde: page table page for a wired mapping"
		    " is missing"));

		/*
		 * Invalidate the 2- or 4MB page mapping and return
		 * "failure" if the mapping was never accessed or the
		 * allocation of the new page table page fails.
		 */
		if ((oldpde & PG_A) == 0 || (mpte = vm_page_alloc(NULL,
		    va >> PDRSHIFT, VM_ALLOC_NOOBJ | VM_ALLOC_NORMAL |
		    VM_ALLOC_WIRED)) == NULL) {
			SLIST_INIT(&free);
			sva = trunc_4mpage(va);
			pmap_remove_pde(pmap, pde, sva, &free);
			if ((oldpde & PG_G) == 0)
				pmap_invalidate_pde_page(pmap, sva, oldpde);
			vm_page_free_pages_toq(&free, true);
			CTR2(KTR_PMAP, "pmap_demote_pde: failure for va %#x"
			    " in pmap %p", va, pmap);
			return (FALSE);
		}
		if (pmap != kernel_pmap) {
			mpte->ref_count = NPTEPG;
			pmap->pm_stats.resident_count++;
		}
	}
	mptepa = VM_PAGE_TO_PHYS(mpte);

	/*
	 * If the page mapping is in the kernel's address space, then the
	 * KPTmap can provide access to the page table page.  Otherwise,
	 * temporarily map the page table page (mpte) into the kernel's
	 * address space at either PADDR1 or PADDR2. 
	 */
	if (pmap == kernel_pmap)
		firstpte = &KPTmap[i386_btop(trunc_4mpage(va))];
	else if (curthread->td_pinned > 0 && rw_wowned(&pvh_global_lock)) {
		if ((*PMAP1 & PG_FRAME) != mptepa) {
			*PMAP1 = mptepa | PG_RW | PG_V | PG_A | PG_M;
#ifdef SMP
			PMAP1cpu = PCPU_GET(cpuid);
#endif
			invlcaddr(PADDR1);
			PMAP1changed++;
		} else
#ifdef SMP
		if (PMAP1cpu != PCPU_GET(cpuid)) {
			PMAP1cpu = PCPU_GET(cpuid);
			invlcaddr(PADDR1);
			PMAP1changedcpu++;
		} else
#endif
			PMAP1unchanged++;
		firstpte = PADDR1;
	} else {
		mtx_lock(&PMAP2mutex);
		if ((*PMAP2 & PG_FRAME) != mptepa) {
			*PMAP2 = mptepa | PG_RW | PG_V | PG_A | PG_M;
			pmap_invalidate_page_int(kernel_pmap,
			    (vm_offset_t)PADDR2);
		}
		firstpte = PADDR2;
	}
	newpde = mptepa | PG_M | PG_A | (oldpde & PG_U) | PG_RW | PG_V;
	KASSERT((oldpde & PG_A) != 0,
	    ("pmap_demote_pde: oldpde is missing PG_A"));
	KASSERT((oldpde & (PG_M | PG_RW)) != PG_RW,
	    ("pmap_demote_pde: oldpde is missing PG_M"));
	newpte = oldpde & ~PG_PS;
	if ((newpte & PG_PDE_PAT) != 0)
		newpte ^= PG_PDE_PAT | PG_PTE_PAT;

	/*
	 * If the page table page is not leftover from an earlier promotion,
	 * initialize it.
	 */
	if (mpte->valid == 0)
		pmap_fill_ptp(firstpte, newpte);

	KASSERT((*firstpte & PG_FRAME) == (newpte & PG_FRAME),
	    ("pmap_demote_pde: firstpte and newpte map different physical"
	    " addresses"));

	/*
	 * If the mapping has changed attributes, update the page table
	 * entries.
	 */ 
	if ((*firstpte & PG_PTE_PROMOTE) != (newpte & PG_PTE_PROMOTE))
		pmap_fill_ptp(firstpte, newpte);
	
	/*
	 * Demote the mapping.  This pmap is locked.  The old PDE has
	 * PG_A set.  If the old PDE has PG_RW set, it also has PG_M
	 * set.  Thus, there is no danger of a race with another
	 * processor changing the setting of PG_A and/or PG_M between
	 * the read above and the store below. 
	 */
	if (workaround_erratum383)
		pmap_update_pde(pmap, va, pde, newpde);
	else if (pmap == kernel_pmap)
		pmap_kenter_pde(va, newpde);
	else
		pde_store(pde, newpde);	
	if (firstpte == PADDR2)
		mtx_unlock(&PMAP2mutex);

	/*
	 * Invalidate the recursive mapping of the page table page.
	 */
	pmap_invalidate_page_int(pmap, (vm_offset_t)vtopte(va));

	/*
	 * Demote the pv entry.  This depends on the earlier demotion
	 * of the mapping.  Specifically, the (re)creation of a per-
	 * page pv entry might trigger the execution of pmap_collect(),
	 * which might reclaim a newly (re)created per-page pv entry
	 * and destroy the associated mapping.  In order to destroy
	 * the mapping, the PDE must have already changed from mapping
	 * the 2mpage to referencing the page table page.
	 */
	if ((oldpde & PG_MANAGED) != 0)
		pmap_pv_demote_pde(pmap, va, oldpde & PG_PS_FRAME);

	pmap_pde_demotions++;
	CTR2(KTR_PMAP, "pmap_demote_pde: success for va %#x"
	    " in pmap %p", va, pmap);
	return (TRUE);
}