#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
struct md_page {int pv_gen; int /*<<< orphan*/  pv_list; } ;
typedef  TYPE_4__* pv_entry_t ;
typedef  int pt_entry_t ;
typedef  TYPE_5__* pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_30__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_34__ {TYPE_1__ pm_stats; } ;
struct TYPE_33__ {int /*<<< orphan*/  pv_va; } ;
struct TYPE_31__ {int pv_gen; int /*<<< orphan*/  pv_list; } ;
struct TYPE_32__ {int oflags; int flags; TYPE_2__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 int PG_FICTITIOUS ; 
 int PG_PS ; 
 int PG_W ; 
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
 int pmap_accessed_bit (TYPE_5__*) ; 
 int /*<<< orphan*/  pmap_delayed_invl_wait (TYPE_3__*) ; 
 int /*<<< orphan*/  pmap_demote_pde_locked (TYPE_5__*,int*,int /*<<< orphan*/ ,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_invalidate_page (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int pmap_modified_bit (TYPE_5__*) ; 
 int* pmap_pde (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int* pmap_pde_to_pte (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (TYPE_5__*,int) ; 
 int pmap_rw_bit (TYPE_5__*) ; 
 int /*<<< orphan*/  pmap_unuse_pt (TYPE_5__*,int /*<<< orphan*/ ,int,struct spglist*) ; 
 int pte_load_clear (int*) ; 
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
	pt_entry_t *pte, tpte, PG_A, PG_M, PG_RW;
	pd_entry_t *pde;
	vm_offset_t va;
	struct spglist free;
	int pvh_gen, md_gen;

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
		pde = pmap_pde(pmap, va);
		(void)pmap_demote_pde_locked(pmap, pde, va, &lock);
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
		PG_A = pmap_accessed_bit(pmap);
		PG_M = pmap_modified_bit(pmap);
		PG_RW = pmap_rw_bit(pmap);
		pmap_resident_count_dec(pmap, 1);
		pde = pmap_pde(pmap, pv->pv_va);
		KASSERT((*pde & PG_PS) == 0, ("pmap_remove_all: found"
		    " a 2mpage in page %p's pv list", m));
		pte = pmap_pde_to_pte(pde, pv->pv_va);
		tpte = pte_load_clear(pte);
		if (tpte & PG_W)
			pmap->pm_stats.wired_count--;
		if (tpte & PG_A)
			vm_page_aflag_set(m, PGA_REFERENCED);

		/*
		 * Update the vm_page_t clean and reference bits.
		 */
		if ((tpte & (PG_M | PG_RW)) == (PG_M | PG_RW))
			vm_page_dirty(m);
		pmap_unuse_pt(pmap, pv->pv_va, *pde, &free);
		pmap_invalidate_page(pmap, pv->pv_va);
		TAILQ_REMOVE(&m->md.pv_list, pv, pv_next);
		m->md.pv_gen++;
		free_pv_entry(pmap, pv);
		PMAP_UNLOCK(pmap);
	}
	vm_page_aflag_clear(m, PGA_WRITEABLE);
	rw_wunlock(lock);
	pmap_delayed_invl_wait(m);
	vm_page_free_pages_toq(&free, true);
}