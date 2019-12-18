#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint8_t ;
typedef  scalar_t__ pte_t ;
typedef  TYPE_4__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_14__ {int /*<<< orphan*/  resident_count; int /*<<< orphan*/  wired_count; } ;
struct TYPE_16__ {TYPE_2__ pm_stats; scalar_t__** pm_pdir; } ;
struct TYPE_13__ {int pv_tracked; int /*<<< orphan*/  pv_list; } ;
struct TYPE_15__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (scalar_t__*,char*) ; 
 unsigned int PDIR_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 TYPE_3__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 unsigned int PTBL_IDX (int /*<<< orphan*/ ) ; 
 int PTBL_UNHOLD ; 
 scalar_t__ PTE_ISMANAGED (scalar_t__*) ; 
 scalar_t__ PTE_ISMODIFIED (scalar_t__*) ; 
 scalar_t__ PTE_ISREFERENCED (scalar_t__*) ; 
 int /*<<< orphan*/  PTE_ISVALID (scalar_t__*) ; 
 scalar_t__ PTE_ISWIRED (scalar_t__*) ; 
 int /*<<< orphan*/  PTE_PA (scalar_t__*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_4__* kernel_pmap ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int ptbl_unhold (int /*<<< orphan*/ ,TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  pv_remove (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  tlb0_flush_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_miss_lock () ; 
 int /*<<< orphan*/  tlb_miss_unlock () ; 
 int /*<<< orphan*/  tlbivax_mutex ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_3__*) ; 

__attribute__((used)) static int
pte_remove(mmu_t mmu, pmap_t pmap, vm_offset_t va, uint8_t flags)
{
	unsigned int pdir_idx = PDIR_IDX(va);
	unsigned int ptbl_idx = PTBL_IDX(va);
	vm_page_t m;
	pte_t *ptbl;
	pte_t *pte;

	//int su = (pmap == kernel_pmap);
	//debugf("pte_remove: s (su = %d pmap = 0x%08x va = 0x%08x flags = %d)\n",
	//		su, (u_int32_t)pmap, va, flags);

	ptbl = pmap->pm_pdir[pdir_idx];
	KASSERT(ptbl, ("pte_remove: null ptbl"));

	pte = &ptbl[ptbl_idx];

	if (pte == NULL || !PTE_ISVALID(pte))
		return (0);

	if (PTE_ISWIRED(pte))
		pmap->pm_stats.wired_count--;

	/* Get vm_page_t for mapped pte. */
	m = PHYS_TO_VM_PAGE(PTE_PA(pte));

	/* Handle managed entry. */
	if (PTE_ISMANAGED(pte)) {

		if (PTE_ISMODIFIED(pte))
			vm_page_dirty(m);

		if (PTE_ISREFERENCED(pte))
			vm_page_aflag_set(m, PGA_REFERENCED);

		pv_remove(pmap, va, m);
	} else if (pmap == kernel_pmap && m && m->md.pv_tracked) {
		/*
		 * Always pv_insert()/pv_remove() on MPC85XX, in case DPAA is
		 * used.  This is needed by the NCSW support code for fast
		 * VA<->PA translation.
		 */
		pv_remove(pmap, va, m);
		if (TAILQ_EMPTY(&m->md.pv_list))
			m->md.pv_tracked = false;
	}

	mtx_lock_spin(&tlbivax_mutex);
	tlb_miss_lock();

	tlb0_flush_entry(va);
	*pte = 0;

	tlb_miss_unlock();
	mtx_unlock_spin(&tlbivax_mutex);

	pmap->pm_stats.resident_count--;

	if (flags & PTBL_UNHOLD) {
		//debugf("pte_remove: e (unhold)\n");
		return (ptbl_unhold(mmu, pmap, pdir_idx));
	}

	//debugf("pte_remove: e\n");
	return (0);
}