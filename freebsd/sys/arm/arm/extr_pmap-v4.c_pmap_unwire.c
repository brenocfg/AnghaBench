#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct l2_bucket {int /*<<< orphan*/ * l2b_kva; } ;
typedef  TYPE_3__* pv_entry_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  TYPE_4__* pmap_t ;
struct TYPE_14__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_17__ {TYPE_1__ pm_stats; } ;
struct TYPE_16__ {int pv_flags; } ;
struct TYPE_15__ {int oflags; } ;

/* Variables and functions */
 scalar_t__ L2_NEXT_BUCKET (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_2__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_4__*) ; 
 int PVF_WIRED ; 
 int VPO_UNMANAGED ; 
 size_t l2pte_index (scalar_t__) ; 
 int /*<<< orphan*/  l2pte_pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_3__*) ; 
 TYPE_3__* pmap_find_pv (TYPE_2__*,TYPE_4__*,scalar_t__) ; 
 struct l2_bucket* pmap_get_l2_bucket (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

void
pmap_unwire(pmap_t pmap, vm_offset_t sva, vm_offset_t eva)
{
	struct l2_bucket *l2b;
	pt_entry_t *ptep, pte;
	pv_entry_t pv;
	vm_offset_t next_bucket;
	vm_page_t m;

	rw_wlock(&pvh_global_lock);
	PMAP_LOCK(pmap);
	while (sva < eva) {
		next_bucket = L2_NEXT_BUCKET(sva);
		if (next_bucket > eva)
			next_bucket = eva;
		l2b = pmap_get_l2_bucket(pmap, sva);
		if (l2b == NULL) {
			sva = next_bucket;
			continue;
		}
		for (ptep = &l2b->l2b_kva[l2pte_index(sva)]; sva < next_bucket;
		    sva += PAGE_SIZE, ptep++) {
			if ((pte = *ptep) == 0 ||
			    (m = PHYS_TO_VM_PAGE(l2pte_pa(pte))) == NULL ||
			    (m->oflags & VPO_UNMANAGED) != 0)
				continue;
			pv = pmap_find_pv(m, pmap, sva);
			if ((pv->pv_flags & PVF_WIRED) == 0)
				panic("pmap_unwire: pv %p isn't wired", pv);
			pv->pv_flags &= ~PVF_WIRED;
			pmap->pm_stats.wired_count--;
		}
	}
	rw_wunlock(&pvh_global_lock);
 	PMAP_UNLOCK(pmap);
}