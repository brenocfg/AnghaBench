#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct pv_chunk {int* pc_map; int /*<<< orphan*/ * pc_pventry; TYPE_1__* pc_pmap; } ;
typedef  int /*<<< orphan*/ * pv_entry_t ;
typedef  TYPE_1__* pmap_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  pm_pvchunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PV_STAT (int) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 struct pv_chunk* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int _NPCM ; 
 int _NPCPV ; 
 int ffs (int) ; 
 int /*<<< orphan*/  pc_chunk_allocs ; 
 int /*<<< orphan*/  pc_chunk_count ; 
 int /*<<< orphan*/  pc_chunk_tryfail ; 
 unsigned long* pc_freemask ; 
 int /*<<< orphan*/  pc_list ; 
 int /*<<< orphan*/  pc_lru ; 
 scalar_t__ pmap_pte2list_alloc (scalar_t__*) ; 
 int /*<<< orphan*/ * pmap_pv_reclaim (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_qenter (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pv_chunks ; 
 int /*<<< orphan*/  pv_entry_allocs ; 
 scalar_t__ pv_entry_count ; 
 scalar_t__ pv_entry_high_water ; 
 int pv_entry_spare ; 
 scalar_t__ pv_vafree ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 scalar_t__ ratecheck (struct timeval*,struct timeval const*) ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static pv_entry_t
get_pv_entry(pmap_t pmap, boolean_t try)
{
	static const struct timeval printinterval = { 60, 0 };
	static struct timeval lastprint;
	int bit, field;
	pv_entry_t pv;
	struct pv_chunk *pc;
	vm_page_t m;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	PV_STAT(pv_entry_allocs++);
	pv_entry_count++;
	if (pv_entry_count > pv_entry_high_water)
		if (ratecheck(&lastprint, &printinterval))
			printf("Approaching the limit on PV entries, consider "
			    "increasing either the vm.pmap.shpgperproc or the "
			    "vm.pmap.pv_entries tunable.\n");
retry:
	pc = TAILQ_FIRST(&pmap->pm_pvchunk);
	if (pc != NULL) {
		for (field = 0; field < _NPCM; field++) {
			if (pc->pc_map[field]) {
				bit = ffs(pc->pc_map[field]) - 1;
				break;
			}
		}
		if (field < _NPCM) {
			pv = &pc->pc_pventry[field * 32 + bit];
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
	/*
	 * Access to the pte2list "pv_vafree" is synchronized by the pvh
	 * global lock.  If "pv_vafree" is currently non-empty, it will
	 * remain non-empty until pmap_pte2list_alloc() completes.
	 */
	if (pv_vafree == 0 || (m = vm_page_alloc(NULL, 0, VM_ALLOC_NORMAL |
	    VM_ALLOC_NOOBJ | VM_ALLOC_WIRED)) == NULL) {
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
	pc = (struct pv_chunk *)pmap_pte2list_alloc(&pv_vafree);
	pmap_qenter((vm_offset_t)pc, &m, 1);
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