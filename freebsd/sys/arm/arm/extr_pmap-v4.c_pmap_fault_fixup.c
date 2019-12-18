#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  size_t u_int ;
struct TYPE_8__ {int pvh_attrs; } ;
struct vm_page {TYPE_1__ md; } ;
struct pv_entry {int pv_flags; } ;
struct l2_dtable {struct l2_bucket* l2_bucket; } ;
struct l2_bucket {int* l2b_kva; int l2b_phys; } ;
typedef  int pt_entry_t ;
typedef  TYPE_3__* pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_10__ {TYPE_2__* pm_l1; int /*<<< orphan*/  pm_domain; struct l2_dtable** pm_l2; } ;
struct TYPE_9__ {int* l1_kva; int l1_domain_use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  Debugger () ; 
 int L1_C_DOM (int /*<<< orphan*/ ) ; 
 int L1_C_PROTO ; 
 size_t L1_IDX (scalar_t__) ; 
 size_t L2_BUCKET (size_t) ; 
 size_t L2_IDX (size_t) ; 
 int L2_S_PROTO ; 
 int L2_S_PROT_U ; 
 int L2_S_PROT_W ; 
 int L2_TYPE_INV ; 
 int L2_TYPE_MASK ; 
 struct vm_page* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 int PVF_MOD ; 
 int PVF_REF ; 
 int PVF_WRITE ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  cpu_cpwait () ; 
 int /*<<< orphan*/  cpu_tlb_flushID_SE (scalar_t__) ; 
 size_t l2pte_index (scalar_t__) ; 
 int /*<<< orphan*/  l2pte_pa (int) ; 
 int last_fault_code ; 
 struct pv_entry* pmap_find_pv (struct vm_page*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vector_page ; 
 int /*<<< orphan*/  vm_page_dirty (struct vm_page*) ; 

int
pmap_fault_fixup(pmap_t pm, vm_offset_t va, vm_prot_t ftype, int user)
{
	struct l2_dtable *l2;
	struct l2_bucket *l2b;
	pd_entry_t *pl1pd, l1pd;
	pt_entry_t *ptep, pte;
	vm_paddr_t pa;
	u_int l1idx;
	int rv = 0;

	l1idx = L1_IDX(va);
	rw_wlock(&pvh_global_lock);
	PMAP_LOCK(pm);

	/*
	 * If there is no l2_dtable for this address, then the process
	 * has no business accessing it.
	 *
	 * Note: This will catch userland processes trying to access
	 * kernel addresses.
	 */
	l2 = pm->pm_l2[L2_IDX(l1idx)];
	if (l2 == NULL)
		goto out;

	/*
	 * Likewise if there is no L2 descriptor table
	 */
	l2b = &l2->l2_bucket[L2_BUCKET(l1idx)];
	if (l2b->l2b_kva == NULL)
		goto out;

	/*
	 * Check the PTE itself.
	 */
	ptep = &l2b->l2b_kva[l2pte_index(va)];
	pte = *ptep;
	if (pte == 0)
		goto out;

	/*
	 * Catch a userland access to the vector page mapped at 0x0
	 */
	if (user && (pte & L2_S_PROT_U) == 0)
		goto out;
	if (va == vector_page)
		goto out;

	pa = l2pte_pa(pte);

	if ((ftype & VM_PROT_WRITE) && (pte & L2_S_PROT_W) == 0) {
		/*
		 * This looks like a good candidate for "page modified"
		 * emulation...
		 */
		struct pv_entry *pv;
		struct vm_page *pg;

		/* Extract the physical address of the page */
		if ((pg = PHYS_TO_VM_PAGE(pa)) == NULL) {
			goto out;
		}
		/* Get the current flags for this page. */

		pv = pmap_find_pv(pg, pm, va);
		if (pv == NULL) {
			goto out;
		}

		/*
		 * Do the flags say this page is writable? If not then it
		 * is a genuine write fault. If yes then the write fault is
		 * our fault as we did not reflect the write access in the
		 * PTE. Now we know a write has occurred we can correct this
		 * and also set the modified bit
		 */
		if ((pv->pv_flags & PVF_WRITE) == 0) {
			goto out;
		}

		pg->md.pvh_attrs |= PVF_REF | PVF_MOD;
		vm_page_dirty(pg);
		pv->pv_flags |= PVF_REF | PVF_MOD;

		/*
		 * Re-enable write permissions for the page.  No need to call
		 * pmap_fix_cache(), since this is just a
		 * modified-emulation fault, and the PVF_WRITE bit isn't
		 * changing. We've already set the cacheable bits based on
		 * the assumption that we can write to this page.
		 */
		*ptep = (pte & ~L2_TYPE_MASK) | L2_S_PROTO | L2_S_PROT_W;
		PTE_SYNC(ptep);
		rv = 1;
	} else
	if ((pte & L2_TYPE_MASK) == L2_TYPE_INV) {
		/*
		 * This looks like a good candidate for "page referenced"
		 * emulation.
		 */
		struct pv_entry *pv;
		struct vm_page *pg;

		/* Extract the physical address of the page */
		if ((pg = PHYS_TO_VM_PAGE(pa)) == NULL)
			goto out;
		/* Get the current flags for this page. */

		pv = pmap_find_pv(pg, pm, va);
		if (pv == NULL)
			goto out;

		pg->md.pvh_attrs |= PVF_REF;
		pv->pv_flags |= PVF_REF;


		*ptep = (pte & ~L2_TYPE_MASK) | L2_S_PROTO;
		PTE_SYNC(ptep);
		rv = 1;
	}

	/*
	 * We know there is a valid mapping here, so simply
	 * fix up the L1 if necessary.
	 */
	pl1pd = &pm->pm_l1->l1_kva[l1idx];
	l1pd = l2b->l2b_phys | L1_C_DOM(pm->pm_domain) | L1_C_PROTO;
	if (*pl1pd != l1pd) {
		*pl1pd = l1pd;
		PTE_SYNC(pl1pd);
		rv = 1;
	}

#ifdef DEBUG
	/*
	 * If 'rv == 0' at this point, it generally indicates that there is a
	 * stale TLB entry for the faulting address. This happens when two or
	 * more processes are sharing an L1. Since we don't flush the TLB on
	 * a context switch between such processes, we can take domain faults
	 * for mappings which exist at the same VA in both processes. EVEN IF
	 * WE'VE RECENTLY FIXED UP THE CORRESPONDING L1 in pmap_enter(), for
	 * example.
	 *
	 * This is extremely likely to happen if pmap_enter() updated the L1
	 * entry for a recently entered mapping. In this case, the TLB is
	 * flushed for the new mapping, but there may still be TLB entries for
	 * other mappings belonging to other processes in the 1MB range
	 * covered by the L1 entry.
	 *
	 * Since 'rv == 0', we know that the L1 already contains the correct
	 * value, so the fault must be due to a stale TLB entry.
	 *
	 * Since we always need to flush the TLB anyway in the case where we
	 * fixed up the L1, or frobbed the L2 PTE, we effectively deal with
	 * stale TLB entries dynamically.
	 *
	 * However, the above condition can ONLY happen if the current L1 is
	 * being shared. If it happens when the L1 is unshared, it indicates
	 * that other parts of the pmap are not doing their job WRT managing
	 * the TLB.
	 */
	if (rv == 0 && pm->pm_l1->l1_domain_use_count == 1) {
		printf("fixup: pm %p, va 0x%lx, ftype %d - nothing to do!\n",
		    pm, (u_long)va, ftype);
		printf("fixup: l2 %p, l2b %p, ptep %p, pl1pd %p\n",
		    l2, l2b, ptep, pl1pd);
		printf("fixup: pte 0x%x, l1pd 0x%x, last code 0x%x\n",
		    pte, l1pd, last_fault_code);
#ifdef DDB
		Debugger();
#endif
	}
#endif

	cpu_tlb_flushID_SE(va);
	cpu_cpwait();

	rv = 1;

out:
	rw_wunlock(&pvh_global_lock);
	PMAP_UNLOCK(pm);
	return (rv);
}