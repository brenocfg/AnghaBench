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
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
struct md_page {int pv_gen; int /*<<< orphan*/  pv_list; } ;
typedef  TYPE_4__* pv_entry_t ;
typedef  int pt_entry_t ;
typedef  TYPE_5__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_27__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_31__ {TYPE_1__ pm_stats; } ;
struct TYPE_30__ {int /*<<< orphan*/  pv_va; } ;
struct TYPE_28__ {int pv_gen; int /*<<< orphan*/  pv_list; } ;
struct TYPE_29__ {int oflags; int flags; TYPE_2__ md; } ;

/* Variables and functions */
 int ATTR_AF ; 
 int ATTR_SW_WIRED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  PMAP_TRYLOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_5__*) ; 
 TYPE_5__* PV_PMAP (TYPE_4__*) ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 TYPE_4__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_3__*) ; 
 struct rwlock* VM_PAGE_TO_PV_LIST_LOCK (TYPE_3__*) ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  free_pv_entry (TYPE_5__*,TYPE_4__*) ; 
 struct md_page* pa_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_demote_l2_locked (TYPE_5__*,int*,int /*<<< orphan*/ ,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_invalidate_page (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int* pmap_l2_to_l3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_load (int /*<<< orphan*/ *) ; 
 int pmap_load_clear (int*) ; 
 int /*<<< orphan*/ * pmap_pde (TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 int* pmap_pte (TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pmap_pte_dirty (int) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (TYPE_5__*,int) ; 
 int /*<<< orphan*/  pmap_unuse_pt (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spglist*) ; 
 struct md_page pv_dummy ; 
 int /*<<< orphan*/  pv_next ; 
 int /*<<< orphan*/  rw_wlock (struct rwlock*) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 

void
pmap_remove_all(vm_page_t m)
{
	struct md_page *pvh;
	pv_entry_t pv;
	pmap_t pmap;
	struct rwlock *lock;
	pd_entry_t *pde, tpde;
	pt_entry_t *pte, tpte;
	vm_offset_t va;
	struct spglist free;
	int lvl, pvh_gen, md_gen;

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("pmap_remove_all: page %p is not managed", m));
	SLIST_INIT(&free);
	lock = VM_PAGE_TO_PV_LIST_LOCK(m);
	pvh = (m->flags & PG_FICTITIOUS) != 0 ? &pv_dummy :
	    pa_to_pvh(VM_PAGE_TO_PHYS(m));
retry:
	rw_wlock(lock);
	while ((pv = TAILQ_FIRST(&pvh->pv_list)) != NULL) {
		pmap = PV_PMAP(pv);
		if (!PMAP_TRYLOCK(pmap)) {
			pvh_gen = pvh->pv_gen;
			rw_wunlock(lock);
			PMAP_LOCK(pmap);
			rw_wlock(lock);
			if (pvh_gen != pvh->pv_gen) {
				rw_wunlock(lock);
				PMAP_UNLOCK(pmap);
				goto retry;
			}
		}
		va = pv->pv_va;
		pte = pmap_pte(pmap, va, &lvl);
		KASSERT(pte != NULL,
		    ("pmap_remove_all: no page table entry found"));
		KASSERT(lvl == 2,
		    ("pmap_remove_all: invalid pte level %d", lvl));

		pmap_demote_l2_locked(pmap, pte, va, &lock);
		PMAP_UNLOCK(pmap);
	}
	while ((pv = TAILQ_FIRST(&m->md.pv_list)) != NULL) {
		pmap = PV_PMAP(pv);
		if (!PMAP_TRYLOCK(pmap)) {
			pvh_gen = pvh->pv_gen;
			md_gen = m->md.pv_gen;
			rw_wunlock(lock);
			PMAP_LOCK(pmap);
			rw_wlock(lock);
			if (pvh_gen != pvh->pv_gen || md_gen != m->md.pv_gen) {
				rw_wunlock(lock);
				PMAP_UNLOCK(pmap);
				goto retry;
			}
		}
		pmap_resident_count_dec(pmap, 1);

		pde = pmap_pde(pmap, pv->pv_va, &lvl);
		KASSERT(pde != NULL,
		    ("pmap_remove_all: no page directory entry found"));
		KASSERT(lvl == 2,
		    ("pmap_remove_all: invalid pde level %d", lvl));
		tpde = pmap_load(pde);

		pte = pmap_l2_to_l3(pde, pv->pv_va);
		tpte = pmap_load_clear(pte);
		if (tpte & ATTR_SW_WIRED)
			pmap->pm_stats.wired_count--;
		if ((tpte & ATTR_AF) != 0) {
			pmap_invalidate_page(pmap, pv->pv_va);
			vm_page_aflag_set(m, PGA_REFERENCED);
		}

		/*
		 * Update the vm_page_t clean and reference bits.
		 */
		if (pmap_pte_dirty(tpte))
			vm_page_dirty(m);
		pmap_unuse_pt(pmap, pv->pv_va, tpde, &free);
		TAILQ_REMOVE(&m->md.pv_list, pv, pv_next);
		m->md.pv_gen++;
		free_pv_entry(pmap, pv);
		PMAP_UNLOCK(pmap);
	}
	vm_page_aflag_clear(m, PGA_WRITEABLE);
	rw_wunlock(lock);
	vm_page_free_pages_toq(&free, true);
}