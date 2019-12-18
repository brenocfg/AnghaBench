#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct pv_chunk {int* pc_map; int /*<<< orphan*/ * pc_pventry; TYPE_2__* pc_pmap; } ;
typedef  int /*<<< orphan*/ * pv_entry_t ;
typedef  TYPE_2__* pmap_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  pm_pvchunk; } ;
struct TYPE_9__ {int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ MIPS_PHYS_TO_DIRECT (int /*<<< orphan*/ ) ; 
 int NBBY ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PV_STAT (int) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 struct pv_chunk* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int /*<<< orphan*/  VM_FREELIST_DIRECT ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int _NPCM ; 
 int _NPCPV ; 
 int /*<<< orphan*/  dump_add_page (int /*<<< orphan*/ ) ; 
 int ffsl (int) ; 
 int /*<<< orphan*/  pc_chunk_allocs ; 
 int /*<<< orphan*/  pc_chunk_count ; 
 int /*<<< orphan*/  pc_chunk_tryfail ; 
 unsigned long* pc_freemask ; 
 int /*<<< orphan*/  pc_list ; 
 int /*<<< orphan*/  pc_lru ; 
 TYPE_1__* pmap_pv_reclaim (TYPE_2__*) ; 
 int /*<<< orphan*/  pv_chunks ; 
 int /*<<< orphan*/  pv_entry_allocs ; 
 int /*<<< orphan*/  pv_entry_count ; 
 int pv_entry_spare ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_page_alloc_freelist (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static pv_entry_t
get_pv_entry(pmap_t pmap, boolean_t try)
{
	struct pv_chunk *pc;
	pv_entry_t pv;
	vm_page_t m;
	int bit, field, idx;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	PV_STAT(pv_entry_allocs++);
	pv_entry_count++;
retry:
	pc = TAILQ_FIRST(&pmap->pm_pvchunk);
	if (pc != NULL) {
		for (field = 0; field < _NPCM; field++) {
			if (pc->pc_map[field]) {
				bit = ffsl(pc->pc_map[field]) - 1;
				break;
			}
		}
		if (field < _NPCM) {
			idx = field * sizeof(pc->pc_map[field]) * NBBY + bit;
			pv = &pc->pc_pventry[idx];
			pc->pc_map[field] &= ~(1ul << bit);
			/* If this was the last item, move it to tail */
			for (field = 0; field < _NPCM; field++)
				if (pc->pc_map[field] != 0) {
					PV_STAT(pv_entry_spare--);
					return (pv);	/* not full, return */
				}
			TAILQ_REMOVE(&pmap->pm_pvchunk, pc, pc_list);
			TAILQ_INSERT_TAIL(&pmap->pm_pvchunk, pc, pc_list);
			PV_STAT(pv_entry_spare--);
			return (pv);
		}
	}
	/* No free items, allocate another chunk */
	m = vm_page_alloc_freelist(VM_FREELIST_DIRECT, VM_ALLOC_NORMAL |
	    VM_ALLOC_WIRED);
	if (m == NULL) {
		if (try) {
			pv_entry_count--;
			PV_STAT(pc_chunk_tryfail++);
			return (NULL);
		}
		m = pmap_pv_reclaim(pmap);
		if (m == NULL)
			goto retry;
	}
	PV_STAT(pc_chunk_count++);
	PV_STAT(pc_chunk_allocs++);
	dump_add_page(m->phys_addr);
	pc = (struct pv_chunk *)MIPS_PHYS_TO_DIRECT(VM_PAGE_TO_PHYS(m));
	pc->pc_pmap = pmap;
	pc->pc_map[0] = pc_freemask[0] & ~1ul;	/* preallocated bit 0 */
	for (field = 1; field < _NPCM; field++)
		pc->pc_map[field] = pc_freemask[field];
	TAILQ_INSERT_TAIL(&pv_chunks, pc, pc_lru);
	pv = &pc->pc_pventry[0];
	TAILQ_INSERT_HEAD(&pmap->pm_pvchunk, pc, pc_list);
	PV_STAT(pv_entry_spare += _NPCPV - 1);
	return (pv);
}