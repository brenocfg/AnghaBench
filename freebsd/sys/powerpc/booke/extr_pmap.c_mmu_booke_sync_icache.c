#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  scalar_t__ pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  PTBL_UNHOLD ; 
 scalar_t__ PTE_ISVALID (int /*<<< orphan*/ *) ; 
 int PTE_PA (int /*<<< orphan*/ *) ; 
 int PTE_SR ; 
 int PTE_VALID ; 
 int /*<<< orphan*/  __syncicache (void*,int) ; 
 int /*<<< orphan*/  curpmap ; 
 scalar_t__ kernel_pmap ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pte_enter (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_find (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pte_remove (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mmu_booke_sync_icache(mmu_t mmu, pmap_t pm, vm_offset_t va, vm_size_t sz)
{
	pte_t *pte;
	vm_paddr_t pa = 0;
	int sync_sz, valid;
#ifndef __powerpc64__
	pmap_t pmap;
	vm_page_t m;
	vm_offset_t addr;
	int active;
#endif
 
#ifndef __powerpc64__
	rw_wlock(&pvh_global_lock);
	pmap = PCPU_GET(curpmap);
	active = (pm == kernel_pmap || pm == pmap) ? 1 : 0;
#endif
	while (sz > 0) {
		PMAP_LOCK(pm);
		pte = pte_find(mmu, pm, va);
		valid = (pte != NULL && PTE_ISVALID(pte)) ? 1 : 0;
		if (valid)
			pa = PTE_PA(pte);
		PMAP_UNLOCK(pm);
		sync_sz = PAGE_SIZE - (va & PAGE_MASK);
		sync_sz = min(sync_sz, sz);
		if (valid) {
#ifdef __powerpc64__
			pa += (va & PAGE_MASK);
			__syncicache((void *)PHYS_TO_DMAP(pa), sync_sz);
#else
			if (!active) {
				/* Create a mapping in the active pmap. */
				addr = 0;
				m = PHYS_TO_VM_PAGE(pa);
				PMAP_LOCK(pmap);
				pte_enter(mmu, pmap, m, addr,
				    PTE_SR | PTE_VALID, FALSE);
				addr += (va & PAGE_MASK);
				__syncicache((void *)addr, sync_sz);
				pte_remove(mmu, pmap, addr, PTBL_UNHOLD);
				PMAP_UNLOCK(pmap);
			} else
				__syncicache((void *)va, sync_sz);
#endif
		}
		va += sync_sz;
		sz -= sync_sz;
	}
#ifndef __powerpc64__
	rw_wunlock(&pvh_global_lock);
#endif
}