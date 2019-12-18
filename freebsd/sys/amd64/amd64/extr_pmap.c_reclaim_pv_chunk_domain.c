#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_21__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  unsigned long uint64_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
struct pv_chunks_list {int active_reclaims; int /*<<< orphan*/  pvc_lock; int /*<<< orphan*/  pvc_list; } ;
struct pv_chunk_header {int dummy; } ;
struct pv_chunk {unsigned long* pc_map; TYPE_4__* pc_pmap; int /*<<< orphan*/  pv_va; struct pv_chunk* pc_pventry; } ;
struct md_page {int /*<<< orphan*/  pv_list; } ;
typedef  struct pv_chunk* pv_entry_t ;
typedef  int pt_entry_t ;
typedef  TYPE_4__* pmap_t ;
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  pc_marker_end_b ;
typedef  int /*<<< orphan*/  pc_marker_b ;
struct TYPE_33__ {int /*<<< orphan*/  pm_pvchunk; } ;
struct TYPE_29__ {int /*<<< orphan*/  pv_list; int /*<<< orphan*/  pv_gen; } ;
struct TYPE_32__ {int flags; int ref_count; int /*<<< orphan*/  phys_addr; TYPE_1__ md; } ;
struct TYPE_31__ {int /*<<< orphan*/  ss; } ;
struct TYPE_30__ {TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_PV_LIST_LOCK_TO_VM_PAGE (struct rwlock**,TYPE_3__*) ; 
 int DMAP_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 unsigned long PC_FREE0 ; 
 unsigned long PC_FREE1 ; 
 unsigned long PC_FREE2 ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 int PG_FICTITIOUS ; 
 int PG_FRAME ; 
 int PG_PS ; 
 int PG_W ; 
 TYPE_3__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_TRYLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PV_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELEASE_PV_LIST_LOCK (struct rwlock**) ; 
 scalar_t__ SLIST_EMPTY (struct spglist*) ; 
 TYPE_3__* SLIST_FIRST (struct spglist*) ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct spglist*,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pv_chunk* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct pv_chunk*,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 struct pv_chunk* TAILQ_NEXT (struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_3__*) ; 
 int _NPCM ; 
 int _NPCPV ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_long (int /*<<< orphan*/ *,int) ; 
 int bsfq (unsigned long) ; 
 int /*<<< orphan*/  bzero (struct pv_chunk_header*,int) ; 
 int /*<<< orphan*/  dump_drop_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct md_page* pa_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc_chunk_count ; 
 int /*<<< orphan*/  pc_chunk_frees ; 
 unsigned long* pc_freemask ; 
 int /*<<< orphan*/  pc_list ; 
 int /*<<< orphan*/  pc_lru ; 
 TYPE_21__ plinks ; 
 int pmap_accessed_bit (TYPE_4__*) ; 
 int /*<<< orphan*/  pmap_delayed_invl_page (TYPE_3__*) ; 
 int /*<<< orphan*/  pmap_delayed_invl_start () ; 
 int pmap_global_bit (TYPE_4__*) ; 
 int /*<<< orphan*/  pmap_invalidate_page (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int pmap_modified_bit (TYPE_4__*) ; 
 int pmap_not_in_di () ; 
 int* pmap_pde (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int* pmap_pde_to_pte (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (TYPE_4__*,int) ; 
 int pmap_rw_bit (TYPE_4__*) ; 
 int /*<<< orphan*/  pmap_unuse_pt (TYPE_4__*,int /*<<< orphan*/ ,int,struct spglist*) ; 
 int pte_load_clear (int*) ; 
 struct pv_chunks_list* pv_chunks ; 
 int /*<<< orphan*/  pv_entry_count ; 
 int /*<<< orphan*/  pv_entry_frees ; 
 int /*<<< orphan*/  pv_entry_spare ; 
 int /*<<< orphan*/  pv_next ; 
 int /*<<< orphan*/  reclaim_pv_chunk_leave_pmap (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 

__attribute__((used)) static vm_page_t
reclaim_pv_chunk_domain(pmap_t locked_pmap, struct rwlock **lockp, int domain)
{
	struct pv_chunks_list *pvc;
	struct pv_chunk *pc, *pc_marker, *pc_marker_end;
	struct pv_chunk_header pc_marker_b, pc_marker_end_b;
	struct md_page *pvh;
	pd_entry_t *pde;
	pmap_t next_pmap, pmap;
	pt_entry_t *pte, tpte;
	pt_entry_t PG_G, PG_A, PG_M, PG_RW;
	pv_entry_t pv;
	vm_offset_t va;
	vm_page_t m, m_pc;
	struct spglist free;
	uint64_t inuse;
	int bit, field, freed;
	bool start_di;

	PMAP_LOCK_ASSERT(locked_pmap, MA_OWNED);
	KASSERT(lockp != NULL, ("reclaim_pv_chunk: lockp is NULL"));
	pmap = NULL;
	m_pc = NULL;
	PG_G = PG_A = PG_M = PG_RW = 0;
	SLIST_INIT(&free);
	bzero(&pc_marker_b, sizeof(pc_marker_b));
	bzero(&pc_marker_end_b, sizeof(pc_marker_end_b));
	pc_marker = (struct pv_chunk *)&pc_marker_b;
	pc_marker_end = (struct pv_chunk *)&pc_marker_end_b;

	/*
	 * A delayed invalidation block should already be active if
	 * pmap_advise() or pmap_remove() called this function by way
	 * of pmap_demote_pde_locked().
	 */
	start_di = pmap_not_in_di();

	pvc = &pv_chunks[domain];
	mtx_lock(&pvc->pvc_lock);
	pvc->active_reclaims++;
	TAILQ_INSERT_HEAD(&pvc->pvc_list, pc_marker, pc_lru);
	TAILQ_INSERT_TAIL(&pvc->pvc_list, pc_marker_end, pc_lru);
	while ((pc = TAILQ_NEXT(pc_marker, pc_lru)) != pc_marker_end &&
	    SLIST_EMPTY(&free)) {
		next_pmap = pc->pc_pmap;
		if (next_pmap == NULL) {
			/*
			 * The next chunk is a marker.  However, it is
			 * not our marker, so active_reclaims must be
			 * > 1.  Consequently, the next_chunk code
			 * will not rotate the pv_chunks list.
			 */
			goto next_chunk;
		}
		mtx_unlock(&pvc->pvc_lock);

		/*
		 * A pv_chunk can only be removed from the pc_lru list
		 * when both pc_chunks_mutex is owned and the
		 * corresponding pmap is locked.
		 */
		if (pmap != next_pmap) {
			reclaim_pv_chunk_leave_pmap(pmap, locked_pmap,
			    start_di);
			pmap = next_pmap;
			/* Avoid deadlock and lock recursion. */
			if (pmap > locked_pmap) {
				RELEASE_PV_LIST_LOCK(lockp);
				PMAP_LOCK(pmap);
				if (start_di)
					pmap_delayed_invl_start();
				mtx_lock(&pvc->pvc_lock);
				continue;
			} else if (pmap != locked_pmap) {
				if (PMAP_TRYLOCK(pmap)) {
					if (start_di)
						pmap_delayed_invl_start();
					mtx_lock(&pvc->pvc_lock);
					continue;
				} else {
					pmap = NULL; /* pmap is not locked */
					mtx_lock(&pvc->pvc_lock);
					pc = TAILQ_NEXT(pc_marker, pc_lru);
					if (pc == NULL ||
					    pc->pc_pmap != next_pmap)
						continue;
					goto next_chunk;
				}
			} else if (start_di)
				pmap_delayed_invl_start();
			PG_G = pmap_global_bit(pmap);
			PG_A = pmap_accessed_bit(pmap);
			PG_M = pmap_modified_bit(pmap);
			PG_RW = pmap_rw_bit(pmap);
		}

		/*
		 * Destroy every non-wired, 4 KB page mapping in the chunk.
		 */
		freed = 0;
		for (field = 0; field < _NPCM; field++) {
			for (inuse = ~pc->pc_map[field] & pc_freemask[field];
			    inuse != 0; inuse &= ~(1UL << bit)) {
				bit = bsfq(inuse);
				pv = &pc->pc_pventry[field * 64 + bit];
				va = pv->pv_va;
				pde = pmap_pde(pmap, va);
				if ((*pde & PG_PS) != 0)
					continue;
				pte = pmap_pde_to_pte(pde, va);
				if ((*pte & PG_W) != 0)
					continue;
				tpte = pte_load_clear(pte);
				if ((tpte & PG_G) != 0)
					pmap_invalidate_page(pmap, va);
				m = PHYS_TO_VM_PAGE(tpte & PG_FRAME);
				if ((tpte & (PG_M | PG_RW)) == (PG_M | PG_RW))
					vm_page_dirty(m);
				if ((tpte & PG_A) != 0)
					vm_page_aflag_set(m, PGA_REFERENCED);
				CHANGE_PV_LIST_LOCK_TO_VM_PAGE(lockp, m);
				TAILQ_REMOVE(&m->md.pv_list, pv, pv_next);
				m->md.pv_gen++;
				if (TAILQ_EMPTY(&m->md.pv_list) &&
				    (m->flags & PG_FICTITIOUS) == 0) {
					pvh = pa_to_pvh(VM_PAGE_TO_PHYS(m));
					if (TAILQ_EMPTY(&pvh->pv_list)) {
						vm_page_aflag_clear(m,
						    PGA_WRITEABLE);
					}
				}
				pmap_delayed_invl_page(m);
				pc->pc_map[field] |= 1UL << bit;
				pmap_unuse_pt(pmap, va, *pde, &free);
				freed++;
			}
		}
		if (freed == 0) {
			mtx_lock(&pvc->pvc_lock);
			goto next_chunk;
		}
		/* Every freed mapping is for a 4 KB page. */
		pmap_resident_count_dec(pmap, freed);
		PV_STAT(atomic_add_long(&pv_entry_frees, freed));
		PV_STAT(atomic_add_int(&pv_entry_spare, freed));
		PV_STAT(atomic_subtract_long(&pv_entry_count, freed));
		TAILQ_REMOVE(&pmap->pm_pvchunk, pc, pc_list);
		if (pc->pc_map[0] == PC_FREE0 && pc->pc_map[1] == PC_FREE1 &&
		    pc->pc_map[2] == PC_FREE2) {
			PV_STAT(atomic_subtract_int(&pv_entry_spare, _NPCPV));
			PV_STAT(atomic_subtract_int(&pc_chunk_count, 1));
			PV_STAT(atomic_add_int(&pc_chunk_frees, 1));
			/* Entire chunk is free; return it. */
			m_pc = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)pc));
			dump_drop_page(m_pc->phys_addr);
			mtx_lock(&pvc->pvc_lock);
			TAILQ_REMOVE(&pvc->pvc_list, pc, pc_lru);
			break;
		}
		TAILQ_INSERT_HEAD(&pmap->pm_pvchunk, pc, pc_list);
		mtx_lock(&pvc->pvc_lock);
		/* One freed pv entry in locked_pmap is sufficient. */
		if (pmap == locked_pmap)
			break;
next_chunk:
		TAILQ_REMOVE(&pvc->pvc_list, pc_marker, pc_lru);
		TAILQ_INSERT_AFTER(&pvc->pvc_list, pc, pc_marker, pc_lru);
		if (pvc->active_reclaims == 1 && pmap != NULL) {
			/*
			 * Rotate the pv chunks list so that we do not
			 * scan the same pv chunks that could not be
			 * freed (because they contained a wired
			 * and/or superpage mapping) on every
			 * invocation of reclaim_pv_chunk().
			 */
			while ((pc = TAILQ_FIRST(&pvc->pvc_list)) != pc_marker) {
				MPASS(pc->pc_pmap != NULL);
				TAILQ_REMOVE(&pvc->pvc_list, pc, pc_lru);
				TAILQ_INSERT_TAIL(&pvc->pvc_list, pc, pc_lru);
			}
		}
	}
	TAILQ_REMOVE(&pvc->pvc_list, pc_marker, pc_lru);
	TAILQ_REMOVE(&pvc->pvc_list, pc_marker_end, pc_lru);
	pvc->active_reclaims--;
	mtx_unlock(&pvc->pvc_lock);
	reclaim_pv_chunk_leave_pmap(pmap, locked_pmap, start_di);
	if (m_pc == NULL && !SLIST_EMPTY(&free)) {
		m_pc = SLIST_FIRST(&free);
		SLIST_REMOVE_HEAD(&free, plinks.s.ss);
		/* Recycle a freed page table page. */
		m_pc->ref_count = 1;
	}
	vm_page_free_pages_toq(&free, true);
	return (m_pc);
}