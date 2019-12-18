#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_10__ {scalar_t__ resident_count; } ;
struct TYPE_11__ {TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 int L0_OFFSET ; 
 int L0_SIZE ; 
 int L1_OFFSET ; 
 int L1_SIZE ; 
 int L2_BLOCK ; 
 int L2_OFFSET ; 
 int L2_SIZE ; 
 int L2_TABLE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 int /*<<< orphan*/ * pmap_demote_l2_locked (TYPE_2__*,int /*<<< orphan*/ *,int,struct rwlock**) ; 
 int /*<<< orphan*/ * pmap_l0 (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * pmap_l0_to_l1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pmap_l1_to_l2 (int /*<<< orphan*/ *,int) ; 
 int pmap_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_remove_l2 (TYPE_2__*,int /*<<< orphan*/ *,int,int,struct spglist*,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_remove_l3_range (TYPE_2__*,int,int,int,struct spglist*,struct rwlock**) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 

void
pmap_remove(pmap_t pmap, vm_offset_t sva, vm_offset_t eva)
{
	struct rwlock *lock;
	vm_offset_t va_next;
	pd_entry_t *l0, *l1, *l2;
	pt_entry_t l3_paddr;
	struct spglist free;

	/*
	 * Perform an unsynchronized read.  This is, however, safe.
	 */
	if (pmap->pm_stats.resident_count == 0)
		return;

	SLIST_INIT(&free);

	PMAP_LOCK(pmap);

	lock = NULL;
	for (; sva < eva; sva = va_next) {

		if (pmap->pm_stats.resident_count == 0)
			break;

		l0 = pmap_l0(pmap, sva);
		if (pmap_load(l0) == 0) {
			va_next = (sva + L0_SIZE) & ~L0_OFFSET;
			if (va_next < sva)
				va_next = eva;
			continue;
		}

		l1 = pmap_l0_to_l1(l0, sva);
		if (pmap_load(l1) == 0) {
			va_next = (sva + L1_SIZE) & ~L1_OFFSET;
			if (va_next < sva)
				va_next = eva;
			continue;
		}

		/*
		 * Calculate index for next page table.
		 */
		va_next = (sva + L2_SIZE) & ~L2_OFFSET;
		if (va_next < sva)
			va_next = eva;

		l2 = pmap_l1_to_l2(l1, sva);
		if (l2 == NULL)
			continue;

		l3_paddr = pmap_load(l2);

		if ((l3_paddr & ATTR_DESCR_MASK) == L2_BLOCK) {
			if (sva + L2_SIZE == va_next && eva >= va_next) {
				pmap_remove_l2(pmap, l2, sva, pmap_load(l1),
				    &free, &lock);
				continue;
			} else if (pmap_demote_l2_locked(pmap, l2, sva,
			    &lock) == NULL)
				continue;
			l3_paddr = pmap_load(l2);
		}

		/*
		 * Weed out invalid mappings.
		 */
		if ((l3_paddr & ATTR_DESCR_MASK) != L2_TABLE)
			continue;

		/*
		 * Limit our scan to either the end of the va represented
		 * by the current page table page, or to the end of the
		 * range being removed.
		 */
		if (va_next > eva)
			va_next = eva;

		pmap_remove_l3_range(pmap, l3_paddr, sva, va_next, &free,
		    &lock);
	}
	if (lock != NULL)
		rw_wunlock(lock);
	PMAP_UNLOCK(pmap);
	vm_page_free_pages_toq(&free, true);
}