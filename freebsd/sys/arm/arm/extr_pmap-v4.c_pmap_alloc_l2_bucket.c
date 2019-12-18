#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_short ;
struct l2_dtable {scalar_t__ l2_occupancy; struct l2_bucket* l2_bucket; } ;
struct l2_bucket {int /*<<< orphan*/  l2b_l1idx; struct l2_dtable* l2b_kva; int /*<<< orphan*/  l2b_phys; } ;
typedef  struct l2_dtable pt_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_6__ {struct l2_dtable** pm_l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  L1_IDX (int /*<<< orphan*/ ) ; 
 size_t L2_BUCKET (int /*<<< orphan*/ ) ; 
 size_t L2_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PMAP_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  bzero (struct l2_dtable*,int) ; 
 int /*<<< orphan*/  l2table_zone ; 
 int /*<<< orphan*/  l2zone ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 struct l2_dtable* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct l2_dtable*) ; 
 int /*<<< orphan*/  vtophys (struct l2_dtable*) ; 

__attribute__((used)) static struct l2_bucket *
pmap_alloc_l2_bucket(pmap_t pm, vm_offset_t va)
{
	struct l2_dtable *l2;
	struct l2_bucket *l2b;
	u_short l1idx;

	l1idx = L1_IDX(va);

	PMAP_ASSERT_LOCKED(pm);
	rw_assert(&pvh_global_lock, RA_WLOCKED);
	if ((l2 = pm->pm_l2[L2_IDX(l1idx)]) == NULL) {
		/*
		 * No mapping at this address, as there is
		 * no entry in the L1 table.
		 * Need to allocate a new l2_dtable.
		 */
		PMAP_UNLOCK(pm);
		rw_wunlock(&pvh_global_lock);
		if ((l2 = uma_zalloc(l2table_zone, M_NOWAIT)) == NULL) {
			rw_wlock(&pvh_global_lock);
			PMAP_LOCK(pm);
			return (NULL);
		}
		rw_wlock(&pvh_global_lock);
		PMAP_LOCK(pm);
		if (pm->pm_l2[L2_IDX(l1idx)] != NULL) {
			/*
			 * Someone already allocated the l2_dtable while
			 * we were doing the same.
			 */
			uma_zfree(l2table_zone, l2);
			l2 = pm->pm_l2[L2_IDX(l1idx)];
		} else {
			bzero(l2, sizeof(*l2));
			/*
			 * Link it into the parent pmap
			 */
			pm->pm_l2[L2_IDX(l1idx)] = l2;
		}
	}

	l2b = &l2->l2_bucket[L2_BUCKET(l1idx)];

	/*
	 * Fetch pointer to the L2 page table associated with the address.
	 */
	if (l2b->l2b_kva == NULL) {
		pt_entry_t *ptep;

		/*
		 * No L2 page table has been allocated. Chances are, this
		 * is because we just allocated the l2_dtable, above.
		 */
		l2->l2_occupancy++;
		PMAP_UNLOCK(pm);
		rw_wunlock(&pvh_global_lock);
		ptep = uma_zalloc(l2zone, M_NOWAIT);
		rw_wlock(&pvh_global_lock);
		PMAP_LOCK(pm);
		if (l2b->l2b_kva != NULL) {
			/* We lost the race. */
			l2->l2_occupancy--;
			uma_zfree(l2zone, ptep);
			return (l2b);
		}
		l2b->l2b_phys = vtophys(ptep);
		if (ptep == NULL) {
			/*
			 * Oops, no more L2 page tables available at this
			 * time. We may need to deallocate the l2_dtable
			 * if we allocated a new one above.
			 */
			l2->l2_occupancy--;
			if (l2->l2_occupancy == 0) {
				pm->pm_l2[L2_IDX(l1idx)] = NULL;
				uma_zfree(l2table_zone, l2);
			}
			return (NULL);
		}

		l2b->l2b_kva = ptep;
		l2b->l2b_l1idx = l1idx;
	}

	return (l2b);
}