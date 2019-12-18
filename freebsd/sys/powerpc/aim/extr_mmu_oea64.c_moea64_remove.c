#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct pvo_entry {scalar_t__ pvo_vaddr; } ;
struct pvo_dlist {int dummy; } ;
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_6__ {scalar_t__ resident_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  pmap_pvo; TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 scalar_t__ PVO_VADDR (struct pvo_entry*) ; 
 struct pvo_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 struct pvo_entry* RB_NFIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 int /*<<< orphan*/  SLIST_EMPTY (struct pvo_dlist*) ; 
 struct pvo_entry* SLIST_FIRST (struct pvo_dlist*) ; 
 int /*<<< orphan*/  SLIST_INIT (struct pvo_dlist*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct pvo_dlist*,struct pvo_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct pvo_dlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pvo_entry (struct pvo_entry*) ; 
 int /*<<< orphan*/  moea64_pvo_remove_from_page (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  moea64_pvo_remove_from_pmap (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  pvo_dlink ; 
 int /*<<< orphan*/  pvo_tree ; 

void
moea64_remove(mmu_t mmu, pmap_t pm, vm_offset_t sva, vm_offset_t eva)
{
	struct  pvo_entry *pvo, *tpvo, key;
	struct pvo_dlist tofree;

	/*
	 * Perform an unsynchronized read.  This is, however, safe.
	 */
	if (pm->pm_stats.resident_count == 0)
		return;

	key.pvo_vaddr = sva;

	SLIST_INIT(&tofree);

	PMAP_LOCK(pm);
	for (pvo = RB_NFIND(pvo_tree, &pm->pmap_pvo, &key);
	    pvo != NULL && PVO_VADDR(pvo) < eva; pvo = tpvo) {
		tpvo = RB_NEXT(pvo_tree, &pm->pmap_pvo, pvo);

		/*
		 * For locking reasons, remove this from the page table and
		 * pmap, but save delinking from the vm_page for a second
		 * pass
		 */
		moea64_pvo_remove_from_pmap(mmu, pvo);
		SLIST_INSERT_HEAD(&tofree, pvo, pvo_dlink);
	}
	PMAP_UNLOCK(pm);

	while (!SLIST_EMPTY(&tofree)) {
		pvo = SLIST_FIRST(&tofree);
		SLIST_REMOVE_HEAD(&tofree, pvo_dlink);
		moea64_pvo_remove_from_page(mmu, pvo);
		free_pvo_entry(pvo);
	}
}