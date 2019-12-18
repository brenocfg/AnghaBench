#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ u_int ;
struct vm_page {int dummy; } ;
struct pv_entry {int /*<<< orphan*/  pv_flags; } ;
struct l2_bucket {scalar_t__* l2b_kva; } ;
typedef  scalar_t__ pt_entry_t ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_10__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_11__ {TYPE_1__ pm_stats; } ;

/* Variables and functions */
 scalar_t__ L2_NEXT_BUCKET (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 struct vm_page* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 scalar_t__ PMAP_REMOVE_CLEAN_LIST_SIZE ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PTE_SYNC (scalar_t__*) ; 
 scalar_t__ PV_BEEN_EXECD (int /*<<< orphan*/ ) ; 
 scalar_t__ PV_BEEN_REFD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_dcache_wbinv_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cpu_idcache_wbinv_all () ; 
 int /*<<< orphan*/  cpu_idcache_wbinv_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_all () ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cpu_tlb_flushD_SE (scalar_t__) ; 
 int /*<<< orphan*/  cpu_tlb_flushID () ; 
 int /*<<< orphan*/  cpu_tlb_flushID_SE (scalar_t__) ; 
 size_t l2pte_index (scalar_t__) ; 
 int /*<<< orphan*/  l2pte_pa (scalar_t__) ; 
 scalar_t__ l2pte_valid (scalar_t__) ; 
 int /*<<< orphan*/  pmap_free_l2_bucket (TYPE_2__*,struct l2_bucket*,scalar_t__) ; 
 int /*<<< orphan*/  pmap_free_pv_entry (struct pv_entry*) ; 
 struct l2_bucket* pmap_get_l2_bucket (TYPE_2__*,scalar_t__) ; 
 scalar_t__ pmap_is_current (TYPE_2__*) ; 
 struct pv_entry* pmap_remove_pv (struct vm_page*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

void
pmap_remove(pmap_t pm, vm_offset_t sva, vm_offset_t eva)
{
	struct l2_bucket *l2b;
	vm_offset_t next_bucket;
	pt_entry_t *ptep;
	u_int total;
	u_int mappings, is_exec, is_refd;
	int flushall = 0;


	/*
	 * we lock in the pmap => pv_head direction
	 */

	rw_wlock(&pvh_global_lock);
	PMAP_LOCK(pm);
	total = 0;
	while (sva < eva) {
		/*
		 * Do one L2 bucket's worth at a time.
		 */
		next_bucket = L2_NEXT_BUCKET(sva);
		if (next_bucket > eva)
			next_bucket = eva;

		l2b = pmap_get_l2_bucket(pm, sva);
		if (l2b == NULL) {
			sva = next_bucket;
			continue;
		}

		ptep = &l2b->l2b_kva[l2pte_index(sva)];
		mappings = 0;

		while (sva < next_bucket) {
			struct vm_page *pg;
			pt_entry_t pte;
			vm_paddr_t pa;

			pte = *ptep;

			if (pte == 0) {
				/*
				 * Nothing here, move along
				 */
				sva += PAGE_SIZE;
				ptep++;
				continue;
			}

			pm->pm_stats.resident_count--;
			pa = l2pte_pa(pte);
			is_exec = 0;
			is_refd = 1;

			/*
			 * Update flags. In a number of circumstances,
			 * we could cluster a lot of these and do a
			 * number of sequential pages in one go.
			 */
			if ((pg = PHYS_TO_VM_PAGE(pa)) != NULL) {
				struct pv_entry *pve;

				pve = pmap_remove_pv(pg, pm, sva);
				if (pve) {
					is_exec = PV_BEEN_EXECD(pve->pv_flags);
					is_refd = PV_BEEN_REFD(pve->pv_flags);
					pmap_free_pv_entry(pve);
				}
			}

			if (l2pte_valid(pte) && pmap_is_current(pm)) {
				if (total < PMAP_REMOVE_CLEAN_LIST_SIZE) {
					total++;
			   		if (is_exec) {
        					cpu_idcache_wbinv_range(sva,
						    PAGE_SIZE);
						cpu_l2cache_wbinv_range(sva,
						    PAGE_SIZE);
						cpu_tlb_flushID_SE(sva);
			   		} else if (is_refd) {
						cpu_dcache_wbinv_range(sva,
						    PAGE_SIZE);
						cpu_l2cache_wbinv_range(sva,
						    PAGE_SIZE);
						cpu_tlb_flushD_SE(sva);
					}
				} else if (total == PMAP_REMOVE_CLEAN_LIST_SIZE) {
					/* flushall will also only get set for
					 * for a current pmap
					 */
					cpu_idcache_wbinv_all();
					cpu_l2cache_wbinv_all();
					flushall = 1;
					total++;
				}
			}
			*ptep = 0;
			PTE_SYNC(ptep);

			sva += PAGE_SIZE;
			ptep++;
			mappings++;
		}

		pmap_free_l2_bucket(pm, l2b, mappings);
	}

	rw_wunlock(&pvh_global_lock);
	if (flushall)
		cpu_tlb_flushID();
 	PMAP_UNLOCK(pm);
}