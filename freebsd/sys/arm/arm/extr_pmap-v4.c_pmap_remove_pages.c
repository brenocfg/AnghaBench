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
typedef  TYPE_3__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct pv_entry {int pv_flags; int /*<<< orphan*/  pv_va; } ;
struct l2_bucket {int* l2b_kva; } ;
typedef  int pt_entry_t ;
typedef  TYPE_4__* pmap_t ;
struct TYPE_14__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_17__ {TYPE_1__ pm_stats; int /*<<< orphan*/  pm_pvlist; } ;
struct TYPE_15__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_16__ {TYPE_2__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ KERNBASE ; 
 int L2_S_FRAME ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 TYPE_3__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 int PVF_UNMAN ; 
 int PVF_WIRED ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pv_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pv_entry* TAILQ_NEXT (struct pv_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_cpwait () ; 
 int /*<<< orphan*/  cpu_idcache_wbinv_all () ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_all () ; 
 int /*<<< orphan*/  cpu_tlb_flushID () ; 
 size_t l2pte_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_free_l2_bucket (TYPE_4__*,struct l2_bucket*,int) ; 
 int /*<<< orphan*/  pmap_free_pv_entry (struct pv_entry*) ; 
 struct l2_bucket* pmap_get_l2_bucket (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_nuke_pv (TYPE_3__*,TYPE_4__*,struct pv_entry*) ; 
 int /*<<< orphan*/  pv_plist ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 

void
pmap_remove_pages(pmap_t pmap)
{
	struct pv_entry *pv, *npv;
	struct l2_bucket *l2b = NULL;
	vm_page_t m;
	pt_entry_t *pt;

	rw_wlock(&pvh_global_lock);
	PMAP_LOCK(pmap);
	cpu_idcache_wbinv_all();
	cpu_l2cache_wbinv_all();
	for (pv = TAILQ_FIRST(&pmap->pm_pvlist); pv; pv = npv) {
		if (pv->pv_flags & PVF_WIRED || pv->pv_flags & PVF_UNMAN) {
			/* Cannot remove wired or unmanaged pages now. */
			npv = TAILQ_NEXT(pv, pv_plist);
			continue;
		}
		pmap->pm_stats.resident_count--;
		l2b = pmap_get_l2_bucket(pmap, pv->pv_va);
		KASSERT(l2b != NULL, ("No L2 bucket in pmap_remove_pages"));
		pt = &l2b->l2b_kva[l2pte_index(pv->pv_va)];
		m = PHYS_TO_VM_PAGE(*pt & L2_S_FRAME);
		KASSERT((vm_offset_t)m >= KERNBASE, ("Trying to access non-existent page va %x pte %x", pv->pv_va, *pt));
		*pt = 0;
		PTE_SYNC(pt);
		npv = TAILQ_NEXT(pv, pv_plist);
		pmap_nuke_pv(m, pmap, pv);
		if (TAILQ_EMPTY(&m->md.pv_list))
			vm_page_aflag_clear(m, PGA_WRITEABLE);
		pmap_free_pv_entry(pv);
		pmap_free_l2_bucket(pmap, l2b, 1);
	}
	rw_wunlock(&pvh_global_lock);
	cpu_tlb_flushID();
	cpu_cpwait();
	PMAP_UNLOCK(pmap);
}