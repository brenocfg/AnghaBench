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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_offset_t ;
struct pv_entry {int dummy; } ;
struct l2_bucket {int* l2b_kva; } ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int L2_L_FRAME ; 
 int L2_L_OFFSET ; 
 int L2_S_FRAME ; 
 int L2_S_OFFSET ; 
 int L2_TYPE_L ; 
 int L2_TYPE_MASK ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_cpwait () ; 
 int /*<<< orphan*/  cpu_dcache_wbinv_range (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_range (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_tlb_flushD_SE (int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 size_t l2pte_index (int) ; 
 scalar_t__ l2pte_valid (int) ; 
 int /*<<< orphan*/  pmap_free_pv_entry (struct pv_entry*) ; 
 struct l2_bucket* pmap_get_l2_bucket (int /*<<< orphan*/ ,int) ; 
 struct pv_entry* pmap_remove_pv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/ * pvzone ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_phys_paddr_to_vm_page (int) ; 

void
pmap_kremove(vm_offset_t va)
{
	struct l2_bucket *l2b;
	pt_entry_t *pte, opte;
	struct pv_entry *pve;
	vm_page_t m;
	vm_offset_t pa;

	l2b = pmap_get_l2_bucket(kernel_pmap, va);
	if (!l2b)
		return;
	KASSERT(l2b != NULL, ("No L2 Bucket"));
	pte = &l2b->l2b_kva[l2pte_index(va)];
	opte = *pte;
	if (l2pte_valid(opte)) {
		/* pa = vtophs(va) taken from pmap_extract() */
		if ((opte & L2_TYPE_MASK) == L2_TYPE_L)
			pa = (opte & L2_L_FRAME) | (va & L2_L_OFFSET);
		else
			pa = (opte & L2_S_FRAME) | (va & L2_S_OFFSET);
		/* note: should never have to remove an allocation
		 * before the pvzone is initialized.
		 */
		rw_wlock(&pvh_global_lock);
		PMAP_LOCK(kernel_pmap);
		if (pvzone != NULL && (m = vm_phys_paddr_to_vm_page(pa)) &&
		    (pve = pmap_remove_pv(m, kernel_pmap, va)))
			pmap_free_pv_entry(pve);
		PMAP_UNLOCK(kernel_pmap);
		rw_wunlock(&pvh_global_lock);
		va = va & ~PAGE_MASK;
		cpu_dcache_wbinv_range(va, PAGE_SIZE);
		cpu_l2cache_wbinv_range(va, PAGE_SIZE);
		cpu_tlb_flushD_SE(va);
		cpu_cpwait();
		*pte = 0;
	}
}