#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct l2_bucket {int* l2b_kva; } ;
typedef  TYPE_1__* pv_entry_t ;
typedef  int pt_entry_t ;
typedef  scalar_t__ pmap_t ;
struct TYPE_3__ {scalar_t__ pv_pmap; scalar_t__ pv_va; int pv_flags; } ;

/* Variables and functions */
 int L2_S_CACHE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTE_SYNC_CURRENT (scalar_t__,int*) ; 
 int PVF_WRITE ; 
 scalar_t__ PV_BEEN_EXECD (int) ; 
 scalar_t__ PV_BEEN_REFD (int) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t l2pte_index (scalar_t__) ; 
 scalar_t__ l2pte_valid (int) ; 
 int /*<<< orphan*/  pmap_dcache_wb_range (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct l2_bucket* pmap_get_l2_bucket (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_idcache_wbinv_range (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_tlb_flushD_SE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_tlb_flushID_SE (scalar_t__,scalar_t__) ; 
 int pte_l2_s_cache_mode ; 

__attribute__((used)) static __inline void
pmap_set_cache_entry(pv_entry_t pv, pmap_t pm, vm_offset_t va, int cacheable)
{
	struct l2_bucket *l2b;
	pt_entry_t *ptep, pte;

	l2b = pmap_get_l2_bucket(pv->pv_pmap, pv->pv_va);
	ptep = &l2b->l2b_kva[l2pte_index(pv->pv_va)];

	if (cacheable == 1) {
		pte = (*ptep & ~L2_S_CACHE_MASK) | pte_l2_s_cache_mode;
		if (l2pte_valid(pte)) {
			if (PV_BEEN_EXECD(pv->pv_flags)) {
				pmap_tlb_flushID_SE(pv->pv_pmap, pv->pv_va);
			} else if (PV_BEEN_REFD(pv->pv_flags)) {
				pmap_tlb_flushD_SE(pv->pv_pmap, pv->pv_va);
			}
		}
	} else {
		pte = *ptep &~ L2_S_CACHE_MASK;
		if ((va != pv->pv_va || pm != pv->pv_pmap) &&
			    l2pte_valid(pte)) {
			if (PV_BEEN_EXECD(pv->pv_flags)) {
				pmap_idcache_wbinv_range(pv->pv_pmap,
					    pv->pv_va, PAGE_SIZE);
				pmap_tlb_flushID_SE(pv->pv_pmap, pv->pv_va);
			} else if (PV_BEEN_REFD(pv->pv_flags)) {
				pmap_dcache_wb_range(pv->pv_pmap,
					    pv->pv_va, PAGE_SIZE, TRUE,
					    (pv->pv_flags & PVF_WRITE) == 0);
				pmap_tlb_flushD_SE(pv->pv_pmap,
					    pv->pv_va);
			}
		}
	}
	*ptep = pte;
	PTE_SYNC_CURRENT(pv->pv_pmap, ptep);
}