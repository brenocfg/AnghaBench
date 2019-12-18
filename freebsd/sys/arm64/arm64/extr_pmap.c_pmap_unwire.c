#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_8__ {scalar_t__ wired_count; } ;
struct TYPE_9__ {TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 int ATTR_SW_WIRED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L0_OFFSET ; 
 int L0_SIZE ; 
 int L1_OFFSET ; 
 int L1_SIZE ; 
 int L2_BLOCK ; 
 int L2_OFFSET ; 
 int L2_SIZE ; 
 int L2_TABLE ; 
 scalar_t__ L3_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  pmap_clear_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pmap_demote_l2 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pmap_l0 (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * pmap_l0_to_l1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pmap_l1_to_l2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pmap_l2_to_l3 (int /*<<< orphan*/ *,int) ; 
 int pmap_load (int /*<<< orphan*/ *) ; 

void
pmap_unwire(pmap_t pmap, vm_offset_t sva, vm_offset_t eva)
{
	vm_offset_t va_next;
	pd_entry_t *l0, *l1, *l2;
	pt_entry_t *l3;

	PMAP_LOCK(pmap);
	for (; sva < eva; sva = va_next) {
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

		va_next = (sva + L2_SIZE) & ~L2_OFFSET;
		if (va_next < sva)
			va_next = eva;

		l2 = pmap_l1_to_l2(l1, sva);
		if (pmap_load(l2) == 0)
			continue;

		if ((pmap_load(l2) & ATTR_DESCR_MASK) == L2_BLOCK) {
			if ((pmap_load(l2) & ATTR_SW_WIRED) == 0)
				panic("pmap_unwire: l2 %#jx is missing "
				    "ATTR_SW_WIRED", (uintmax_t)pmap_load(l2));

			/*
			 * Are we unwiring the entire large page?  If not,
			 * demote the mapping and fall through.
			 */
			if (sva + L2_SIZE == va_next && eva >= va_next) {
				pmap_clear_bits(l2, ATTR_SW_WIRED);
				pmap->pm_stats.wired_count -= L2_SIZE /
				    PAGE_SIZE;
				continue;
			} else if (pmap_demote_l2(pmap, l2, sva) == NULL)
				panic("pmap_unwire: demotion failed");
		}
		KASSERT((pmap_load(l2) & ATTR_DESCR_MASK) == L2_TABLE,
		    ("pmap_unwire: Invalid l2 entry after demotion"));

		if (va_next > eva)
			va_next = eva;
		for (l3 = pmap_l2_to_l3(l2, sva); sva != va_next; l3++,
		    sva += L3_SIZE) {
			if (pmap_load(l3) == 0)
				continue;
			if ((pmap_load(l3) & ATTR_SW_WIRED) == 0)
				panic("pmap_unwire: l3 %#jx is missing "
				    "ATTR_SW_WIRED", (uintmax_t)pmap_load(l3));

			/*
			 * ATTR_SW_WIRED must be cleared atomically.  Although
			 * the pmap lock synchronizes access to ATTR_SW_WIRED,
			 * the System MMU may write to the entry concurrently.
			 */
			pmap_clear_bits(l3, ATTR_SW_WIRED);
			pmap->pm_stats.wired_count--;
		}
	}
	PMAP_UNLOCK(pmap);
}