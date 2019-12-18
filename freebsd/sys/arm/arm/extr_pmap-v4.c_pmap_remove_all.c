#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_21__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
struct l2_bucket {scalar_t__* l2b_kva; } ;
typedef  TYPE_4__* pv_entry_t ;
typedef  scalar_t__ pt_entry_t ;
typedef  TYPE_5__* pmap_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_28__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_31__ {TYPE_2__ pm_stats; } ;
struct TYPE_30__ {int pv_flags; TYPE_5__* pv_pmap; int /*<<< orphan*/  pv_va; } ;
struct TYPE_26__ {int /*<<< orphan*/  pv_kva; int /*<<< orphan*/  pv_list; } ;
struct TYPE_29__ {int oflags; TYPE_1__ md; } ;
struct TYPE_27__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  PTE_SYNC_CURRENT (TYPE_5__*,scalar_t__*) ; 
 int PVF_UNMAN ; 
 int /*<<< orphan*/  PVF_WRITE ; 
 scalar_t__ PV_BEEN_EXECD (int) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_4__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  cpu_dcache_inv_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_l2cache_inv_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_21__* curproc ; 
 TYPE_5__* kernel_pmap ; 
 size_t l2pte_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_clearbit (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_free_l2_bucket (TYPE_5__*,struct l2_bucket*,int) ; 
 int /*<<< orphan*/  pmap_free_pv_entry (TYPE_4__*) ; 
 struct l2_bucket* pmap_get_l2_bucket (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_has_valid_mapping (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_is_current (TYPE_5__*) ; 
 int /*<<< orphan*/  pmap_nuke_pv (TYPE_3__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  pmap_tlb_flushD (TYPE_5__*) ; 
 int /*<<< orphan*/  pmap_tlb_flushID (TYPE_5__*) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* vmspace_pmap (int /*<<< orphan*/ ) ; 

void
pmap_remove_all(vm_page_t m)
{
	pv_entry_t pv;
	pt_entry_t *ptep;
	struct l2_bucket *l2b;
	boolean_t flush = FALSE;
	pmap_t curpm;
	int flags = 0;

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("pmap_remove_all: page %p is not managed", m));
	if (TAILQ_EMPTY(&m->md.pv_list))
		return;
	rw_wlock(&pvh_global_lock);

	/*
	 * XXX This call shouldn't exist.  Iterating over the PV list twice,
	 * once in pmap_clearbit() and again below, is both unnecessary and
	 * inefficient.  The below code should itself write back the cache
	 * entry before it destroys the mapping.
	 */
	pmap_clearbit(m, PVF_WRITE);
	curpm = vmspace_pmap(curproc->p_vmspace);
	while ((pv = TAILQ_FIRST(&m->md.pv_list)) != NULL) {
		if (flush == FALSE && (pv->pv_pmap == curpm ||
		    pv->pv_pmap == kernel_pmap))
			flush = TRUE;

		PMAP_LOCK(pv->pv_pmap);
		/*
		 * Cached contents were written-back in pmap_clearbit(),
		 * but we still have to invalidate the cache entry to make
		 * sure stale data are not retrieved when another page will be
		 * mapped under this virtual address.
		 */
		if (pmap_is_current(pv->pv_pmap)) {
			cpu_dcache_inv_range(pv->pv_va, PAGE_SIZE);
			if (pmap_has_valid_mapping(pv->pv_pmap, pv->pv_va))
				cpu_l2cache_inv_range(pv->pv_va, PAGE_SIZE);
		}

		if (pv->pv_flags & PVF_UNMAN) {
			/* remove the pv entry, but do not remove the mapping
			 * and remember this is a kernel mapped page
			 */
			m->md.pv_kva = pv->pv_va;
		} else {
			/* remove the mapping and pv entry */
			l2b = pmap_get_l2_bucket(pv->pv_pmap, pv->pv_va);
			KASSERT(l2b != NULL, ("No l2 bucket"));
			ptep = &l2b->l2b_kva[l2pte_index(pv->pv_va)];
			*ptep = 0;
			PTE_SYNC_CURRENT(pv->pv_pmap, ptep);
			pmap_free_l2_bucket(pv->pv_pmap, l2b, 1);
			pv->pv_pmap->pm_stats.resident_count--;
			flags |= pv->pv_flags;
		}
		pmap_nuke_pv(m, pv->pv_pmap, pv);
		PMAP_UNLOCK(pv->pv_pmap);
		pmap_free_pv_entry(pv);
	}

	if (flush) {
		if (PV_BEEN_EXECD(flags))
			pmap_tlb_flushID(curpm);
		else
			pmap_tlb_flushD(curpm);
	}
	vm_page_aflag_clear(m, PGA_WRITEABLE);
	rw_wunlock(&pvh_global_lock);
}