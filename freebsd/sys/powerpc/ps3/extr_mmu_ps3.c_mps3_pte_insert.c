#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uint64_t ;
struct TYPE_2__ {int slot; } ;
struct pvo_entry {int pvo_vaddr; TYPE_1__ pvo_pte; } ;
struct lpte {int pte_hi; int /*<<< orphan*/  pte_lo; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LPTE_LOCKED ; 
 int LPTE_WIRED ; 
 int /*<<< orphan*/  PTESYNC () ; 
 int PVO_HID ; 
 int /*<<< orphan*/  STAT_MOEA64 (int /*<<< orphan*/ ) ; 
 int lv1_insert_htab_entry (int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  moea64_pte_from_pvo (struct pvo_entry*,struct lpte*) ; 
 int /*<<< orphan*/  moea64_pte_overflow ; 
 int /*<<< orphan*/  moea64_pte_valid ; 
 int moea64_pteg_mask ; 
 int /*<<< orphan*/  mps3_table_lock ; 
 int /*<<< orphan*/  mps3_vas_id ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
mps3_pte_insert(mmu_t mmu, struct pvo_entry *pvo)
{
	int result;
	struct lpte pte, evicted;
	uint64_t index;

	if (pvo->pvo_vaddr & PVO_HID) {
		/* Hypercall needs primary PTEG */
		pvo->pvo_vaddr &= ~PVO_HID;
		pvo->pvo_pte.slot ^= (moea64_pteg_mask << 3);
	}

	pvo->pvo_pte.slot &= ~7UL;
	moea64_pte_from_pvo(pvo, &pte);
	evicted.pte_hi = 0;
	PTESYNC();
	mtx_lock(&mps3_table_lock);
	result = lv1_insert_htab_entry(mps3_vas_id, pvo->pvo_pte.slot,
	    pte.pte_hi, pte.pte_lo, LPTE_LOCKED | LPTE_WIRED, 0,
	    &index, &evicted.pte_hi, &evicted.pte_lo);
	mtx_unlock(&mps3_table_lock);

	if (result != 0) {
		/* No freeable slots in either PTEG? We're hosed. */
		panic("mps3_pte_insert: overflow (%d)", result);
		return (-1);
	}

	/*
	 * See where we ended up.
	 */
	if ((index & ~7UL) != pvo->pvo_pte.slot)
		pvo->pvo_vaddr |= PVO_HID;
	pvo->pvo_pte.slot = index;

	STAT_MOEA64(moea64_pte_valid++);

	if (evicted.pte_hi) {
		KASSERT((evicted.pte_hi & (LPTE_WIRED | LPTE_LOCKED)) == 0,
		    ("Evicted a wired PTE"));
		STAT_MOEA64(moea64_pte_valid--);
		STAT_MOEA64(moea64_pte_overflow++);
	}

	return (0);
}