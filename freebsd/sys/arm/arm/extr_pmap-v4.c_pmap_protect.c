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
typedef  int vm_prot_t ;
typedef  int vm_offset_t ;
typedef  int u_int ;
struct vm_page {int oflags; } ;
struct l2_bucket {int* l2b_kva; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int L2_NEXT_BUCKET (int) ; 
 int L2_S_PROT_W ; 
 int PAGE_SIZE ; 
 struct vm_page* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 int PVF_WRITE ; 
 scalar_t__ PV_BEEN_EXECD (int) ; 
 scalar_t__ PV_BEEN_REFD (int) ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int VPO_UNMANAGED ; 
 size_t l2pte_index (int) ; 
 int /*<<< orphan*/  l2pte_pa (int) ; 
 int /*<<< orphan*/  pmap_dcache_wb_range (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct l2_bucket* pmap_get_l2_bucket (int /*<<< orphan*/ ,int) ; 
 int pmap_modify_pv (struct vm_page*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pmap_tlb_flushD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_tlb_flushD_SE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_tlb_flushID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_tlb_flushID_SE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_dirty (struct vm_page*) ; 

void
pmap_protect(pmap_t pm, vm_offset_t sva, vm_offset_t eva, vm_prot_t prot)
{
	struct l2_bucket *l2b;
	pt_entry_t *ptep, pte;
	vm_offset_t next_bucket;
	u_int flags;
	int flush;

	CTR4(KTR_PMAP, "pmap_protect: pmap %p sva 0x%08x eva 0x%08x prot %x",
	    pm, sva, eva, prot);

	if ((prot & VM_PROT_READ) == 0) {
		pmap_remove(pm, sva, eva);
		return;
	}

	if (prot & VM_PROT_WRITE) {
		/*
		 * If this is a read->write transition, just ignore it and let
		 * vm_fault() take care of it later.
		 */
		return;
	}

	rw_wlock(&pvh_global_lock);
	PMAP_LOCK(pm);

	/*
	 * OK, at this point, we know we're doing write-protect operation.
	 * If the pmap is active, write-back the range.
	 */
	pmap_dcache_wb_range(pm, sva, eva - sva, FALSE, FALSE);

	flush = ((eva - sva) >= (PAGE_SIZE * 4)) ? 0 : -1;
	flags = 0;

	while (sva < eva) {
		next_bucket = L2_NEXT_BUCKET(sva);
		if (next_bucket > eva)
			next_bucket = eva;

		l2b = pmap_get_l2_bucket(pm, sva);
		if (l2b == NULL) {
			sva = next_bucket;
			continue;
		}

		ptep = &l2b->l2b_kva[l2pte_index(sva)];

		while (sva < next_bucket) {
			if ((pte = *ptep) != 0 && (pte & L2_S_PROT_W) != 0) {
				struct vm_page *pg;
				u_int f;

				pg = PHYS_TO_VM_PAGE(l2pte_pa(pte));
				pte &= ~L2_S_PROT_W;
				*ptep = pte;
				PTE_SYNC(ptep);

				if (!(pg->oflags & VPO_UNMANAGED)) {
					f = pmap_modify_pv(pg, pm, sva,
					    PVF_WRITE, 0);
					if (f & PVF_WRITE)
						vm_page_dirty(pg);
				} else
					f = 0;

				if (flush >= 0) {
					flush++;
					flags |= f;
				} else
				if (PV_BEEN_EXECD(f))
					pmap_tlb_flushID_SE(pm, sva);
				else
				if (PV_BEEN_REFD(f))
					pmap_tlb_flushD_SE(pm, sva);
			}

			sva += PAGE_SIZE;
			ptep++;
		}
	}


	if (flush) {
		if (PV_BEEN_EXECD(flags))
			pmap_tlb_flushID(pm);
		else
		if (PV_BEEN_REFD(flags))
			pmap_tlb_flushD(pm);
	}
	rw_wunlock(&pvh_global_lock);

 	PMAP_UNLOCK(pm);
}