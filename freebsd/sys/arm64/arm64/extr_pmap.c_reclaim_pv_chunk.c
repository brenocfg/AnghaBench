#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  unsigned long uint64_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
struct pv_chunk_header {int dummy; } ;
struct pv_chunk {unsigned long* pc_map; TYPE_4__* pc_pmap; int /*<<< orphan*/  pv_va; struct pv_chunk* pc_pventry; } ;
struct md_page {int /*<<< orphan*/  pv_list; } ;
typedef  struct pv_chunk* pv_entry_t ;
typedef  int pt_entry_t ;
typedef  TYPE_4__* pmap_t ;
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  pc_marker_end_b ;
typedef  int /*<<< orphan*/  pc_marker_b ;
struct TYPE_27__ {int /*<<< orphan*/  pm_pvchunk; } ;
struct TYPE_25__ {int /*<<< orphan*/  pv_list; int /*<<< orphan*/  pv_gen; } ;
struct TYPE_26__ {int flags; int ref_count; int /*<<< orphan*/  phys_addr; TYPE_2__ md; } ;
struct TYPE_24__ {int /*<<< orphan*/  ss; } ;
struct TYPE_23__ {TYPE_1__ s; } ;

/* Variables and functions */
 int ATTR_AF ; 
 int ATTR_MASK ; 
 int ATTR_SW_WIRED ; 
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
 TYPE_3__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_TRYLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_4__*) ; 
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
 int /*<<< orphan*/  bzero (struct pv_chunk_header*,int) ; 
 int /*<<< orphan*/  dump_drop_page (int /*<<< orphan*/ ) ; 
 int ffsl (unsigned long) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct md_page* pa_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc_chunk_count ; 
 int /*<<< orphan*/  pc_chunk_frees ; 
 unsigned long* pc_freemask ; 
 int /*<<< orphan*/  pc_list ; 
 int /*<<< orphan*/  pc_lru ; 
 TYPE_14__ plinks ; 
 int /*<<< orphan*/  pmap_invalidate_page (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int* pmap_l2_to_l3 (int*,int /*<<< orphan*/ ) ; 
 int pmap_load (int*) ; 
 int pmap_load_clear (int*) ; 
 int* pmap_pde (TYPE_4__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pmap_pte_dirty (int) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_unuse_pt (TYPE_4__*,int /*<<< orphan*/ ,int,struct spglist*) ; 
 int /*<<< orphan*/  pv_chunks ; 
 int /*<<< orphan*/  pv_chunks_mutex ; 
 int /*<<< orphan*/  pv_entry_count ; 
 int /*<<< orphan*/  pv_entry_frees ; 
 int /*<<< orphan*/  pv_entry_spare ; 
 int /*<<< orphan*/  pv_next ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 

__attribute__((used)) static vm_page_t
reclaim_pv_chunk(pmap_t locked_pmap, struct rwlock **lockp)
{
	struct pv_chunk *pc, *pc_marker, *pc_marker_end;
	struct pv_chunk_header pc_marker_b, pc_marker_end_b;
	struct md_page *pvh;
	pd_entry_t *pde;
	pmap_t next_pmap, pmap;
	pt_entry_t *pte, tpte;
	pv_entry_t pv;
	vm_offset_t va;
	vm_page_t m, m_pc;
	struct spglist free;
	uint64_t inuse;
	int bit, field, freed, lvl;
	static int active_reclaims = 0;

	PMAP_LOCK_ASSERT(locked_pmap, MA_OWNED);
	KASSERT(lockp != NULL, ("reclaim_pv_chunk: lockp is NULL"));

	pmap = NULL;
	m_pc = NULL;
	SLIST_INIT(&free);
	bzero(&pc_marker_b, sizeof(pc_marker_b));
	bzero(&pc_marker_end_b, sizeof(pc_marker_end_b));
	pc_marker = (struct pv_chunk *)&pc_marker_b;
	pc_marker_end = (struct pv_chunk *)&pc_marker_end_b;

	mtx_lock(&pv_chunks_mutex);
	active_reclaims++;
	TAILQ_INSERT_HEAD(&pv_chunks, pc_marker, pc_lru);
	TAILQ_INSERT_TAIL(&pv_chunks, pc_marker_end, pc_lru);
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
		mtx_unlock(&pv_chunks_mutex);

		/*
		 * A pv_chunk can only be removed from the pc_lru list
		 * when both pv_chunks_mutex is owned and the
		 * corresponding pmap is locked.
		 */
		if (pmap != next_pmap) {
			if (pmap != NULL && pmap != locked_pmap)
				PMAP_UNLOCK(pmap);
			pmap = next_pmap;
			/* Avoid deadlock and lock recursion. */
			if (pmap > locked_pmap) {
				RELEASE_PV_LIST_LOCK(lockp);
				PMAP_LOCK(pmap);
				mtx_lock(&pv_chunks_mutex);
				continue;
			} else if (pmap != locked_pmap) {
				if (PMAP_TRYLOCK(pmap)) {
					mtx_lock(&pv_chunks_mutex);
					continue;
				} else {
					pmap = NULL; /* pmap is not locked */
					mtx_lock(&pv_chunks_mutex);
					pc = TAILQ_NEXT(pc_marker, pc_lru);
					if (pc == NULL ||
					    pc->pc_pmap != next_pmap)
						continue;
					goto next_chunk;
				}
			}
		}

		/*
		 * Destroy every non-wired, 4 KB page mapping in the chunk.
		 */
		freed = 0;
		for (field = 0; field < _NPCM; field++) {
			for (inuse = ~pc->pc_map[field] & pc_freemask[field];
			    inuse != 0; inuse &= ~(1UL << bit)) {
				bit = ffsl(inuse) - 1;
				pv = &pc->pc_pventry[field * 64 + bit];
				va = pv->pv_va;
				pde = pmap_pde(pmap, va, &lvl);
				if (lvl != 2)
					continue;
				pte = pmap_l2_to_l3(pde, va);
				tpte = pmap_load(pte);
				if ((tpte & ATTR_SW_WIRED) != 0)
					continue;
				tpte = pmap_load_clear(pte);
				pmap_invalidate_page(pmap, va);
				m = PHYS_TO_VM_PAGE(tpte & ~ATTR_MASK);
				if (pmap_pte_dirty(tpte))
					vm_page_dirty(m);
				if ((tpte & ATTR_AF) != 0)
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
				pc->pc_map[field] |= 1UL << bit;
				pmap_unuse_pt(pmap, va, pmap_load(pde), &free);
				freed++;
			}
		}
		if (freed == 0) {
			mtx_lock(&pv_chunks_mutex);
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
			mtx_lock(&pv_chunks_mutex);
			TAILQ_REMOVE(&pv_chunks, pc, pc_lru);
			break;
		}
		TAILQ_INSERT_HEAD(&pmap->pm_pvchunk, pc, pc_list);
		mtx_lock(&pv_chunks_mutex);
		/* One freed pv entry in locked_pmap is sufficient. */
		if (pmap == locked_pmap)
			break;

next_chunk:
		TAILQ_REMOVE(&pv_chunks, pc_marker, pc_lru);
		TAILQ_INSERT_AFTER(&pv_chunks, pc, pc_marker, pc_lru);
		if (active_reclaims == 1 && pmap != NULL) {
			/*
			 * Rotate the pv chunks list so that we do not
			 * scan the same pv chunks that could not be
			 * freed (because they contained a wired
			 * and/or superpage mapping) on every
			 * invocation of reclaim_pv_chunk().
			 */
			while ((pc = TAILQ_FIRST(&pv_chunks)) != pc_marker) {
				MPASS(pc->pc_pmap != NULL);
				TAILQ_REMOVE(&pv_chunks, pc, pc_lru);
				TAILQ_INSERT_TAIL(&pv_chunks, pc, pc_lru);
			}
		}
	}
	TAILQ_REMOVE(&pv_chunks, pc_marker, pc_lru);
	TAILQ_REMOVE(&pv_chunks, pc_marker_end, pc_lru);
	active_reclaims--;
	mtx_unlock(&pv_chunks_mutex);
	if (pmap != NULL && pmap != locked_pmap)
		PMAP_UNLOCK(pmap);
	if (m_pc == NULL && !SLIST_EMPTY(&free)) {
		m_pc = SLIST_FIRST(&free);
		SLIST_REMOVE_HEAD(&free, plinks.s.ss);
		/* Recycle a freed page table page. */
		m_pc->ref_count = 1;
	}
	vm_page_free_pages_toq(&free, true);
	return (m_pc);
}