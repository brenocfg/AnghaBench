#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int vm_offset_t ;
struct spglist {int dummy; } ;
struct md_page {int /*<<< orphan*/  pv_list; } ;
typedef  TYPE_4__* pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_19__ {int wired_count; scalar_t__ resident_count; } ;
struct TYPE_21__ {TYPE_2__ pm_stats; } ;
struct TYPE_18__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_20__ {scalar_t__ valid; scalar_t__ ref_count; TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int NBPDR ; 
 scalar_t__ NPTEPG ; 
 int PAGE_SIZE ; 
 int PDRMASK ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 int PG_A ; 
 int PG_G ; 
 int PG_M ; 
 int PG_MANAGED ; 
 int PG_PS_FRAME ; 
 int PG_RW ; 
 int PG_W ; 
 TYPE_3__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 TYPE_4__* kernel_pmap ; 
 struct md_page* pa_to_pvh (int) ; 
 int /*<<< orphan*/  pmap_add_delayed_free_list (TYPE_3__*,struct spglist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_pde_page (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  pmap_pvh_free (struct md_page*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_remove_kernel_pde (TYPE_4__*,int*,int) ; 
 TYPE_3__* pmap_remove_pt_page (TYPE_4__*,int) ; 
 int pte_load_clear (int*) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_3__*) ; 

__attribute__((used)) static void
pmap_remove_pde(pmap_t pmap, pd_entry_t *pdq, vm_offset_t sva,
    struct spglist *free)
{
	struct md_page *pvh;
	pd_entry_t oldpde;
	vm_offset_t eva, va;
	vm_page_t m, mpte;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	KASSERT((sva & PDRMASK) == 0,
	    ("pmap_remove_pde: sva is not 4mpage aligned"));
	oldpde = pte_load_clear(pdq);
	if (oldpde & PG_W)
		pmap->pm_stats.wired_count -= NBPDR / PAGE_SIZE;

	/*
	 * Machines that don't support invlpg, also don't support
	 * PG_G.
	 */
	if ((oldpde & PG_G) != 0)
		pmap_invalidate_pde_page(kernel_pmap, sva, oldpde);

	pmap->pm_stats.resident_count -= NBPDR / PAGE_SIZE;
	if (oldpde & PG_MANAGED) {
		pvh = pa_to_pvh(oldpde & PG_PS_FRAME);
		pmap_pvh_free(pvh, pmap, sva);
		eva = sva + NBPDR;
		for (va = sva, m = PHYS_TO_VM_PAGE(oldpde & PG_PS_FRAME);
		    va < eva; va += PAGE_SIZE, m++) {
			if ((oldpde & (PG_M | PG_RW)) == (PG_M | PG_RW))
				vm_page_dirty(m);
			if (oldpde & PG_A)
				vm_page_aflag_set(m, PGA_REFERENCED);
			if (TAILQ_EMPTY(&m->md.pv_list) &&
			    TAILQ_EMPTY(&pvh->pv_list))
				vm_page_aflag_clear(m, PGA_WRITEABLE);
		}
	}
	if (pmap == kernel_pmap) {
		pmap_remove_kernel_pde(pmap, pdq, sva);
	} else {
		mpte = pmap_remove_pt_page(pmap, sva);
		if (mpte != NULL) {
			KASSERT(mpte->valid == VM_PAGE_BITS_ALL,
			    ("pmap_remove_pde: pte page not promoted"));
			pmap->pm_stats.resident_count--;
			KASSERT(mpte->ref_count == NPTEPG,
			    ("pmap_remove_pde: pte page ref count error"));
			mpte->ref_count = 0;
			pmap_add_delayed_free_list(mpte, free, FALSE);
		}
	}
}