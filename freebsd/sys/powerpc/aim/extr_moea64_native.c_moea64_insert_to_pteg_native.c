#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct lpte {void* pte_hi; void* pte_lo; } ;

/* Variables and functions */
 uintptr_t ADDR_API_SHFT64 ; 
 uintptr_t ADDR_PIDX ; 
 uintptr_t ADDR_PIDX_SHFT ; 
 int ADDR_SR_SHFT ; 
 int /*<<< orphan*/  EIEIO () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LPTE_AVPN_MASK ; 
 int LPTE_HID ; 
 int LPTE_VALID ; 
 int LPTE_WIRED ; 
 int /*<<< orphan*/  PTESYNC () ; 
 int /*<<< orphan*/  STAT_MOEA64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLBIE (int) ; 
 scalar_t__ atomic_pte_lock (struct lpte volatile*,int,int*) ; 
 void* htobe64 (void*) ; 
 int mftb () ; 
 int /*<<< orphan*/  moea64_pte_overflow ; 
 int /*<<< orphan*/  moea64_pte_valid ; 
 uintptr_t moea64_pteg_mask ; 
 struct lpte* moea64_pteg_table ; 

__attribute__((used)) static uintptr_t
moea64_insert_to_pteg_native(struct lpte *pvo_pt, uintptr_t slotbase,
    uint64_t mask)
{
	volatile struct lpte *pt;
	uint64_t oldptehi, va;
	uintptr_t k;
	int i, j;

	/* Start at a random slot */
	i = mftb() % 8;
	for (j = 0; j < 8; j++) {
		k = slotbase + (i + j) % 8;
		pt = &moea64_pteg_table[k];
		/* Invalidate and seize lock only if no bits in mask set */
		if (atomic_pte_lock(pt, mask, &oldptehi)) /* Lock obtained */
			break;
	}

	if (j == 8)
		return (-1);

	if (oldptehi & LPTE_VALID) {
		KASSERT(!(oldptehi & LPTE_WIRED), ("Unmapped wired entry"));
		/*
		 * Need to invalidate old entry completely: see
		 * "Modifying a Page Table Entry". Need to reconstruct
		 * the virtual address for the outgoing entry to do that.
		 */
		va = oldptehi >> (ADDR_SR_SHFT - ADDR_API_SHFT64);
		if (oldptehi & LPTE_HID)
			va = (((k >> 3) ^ moea64_pteg_mask) ^ va) &
			    (ADDR_PIDX >> ADDR_PIDX_SHFT);
		else
			va = ((k >> 3) ^ va) & (ADDR_PIDX >> ADDR_PIDX_SHFT);
		va |= (oldptehi & LPTE_AVPN_MASK) <<
		    (ADDR_API_SHFT64 - ADDR_PIDX_SHFT);
		PTESYNC();
		TLBIE(va);
		STAT_MOEA64(moea64_pte_valid--);
		STAT_MOEA64(moea64_pte_overflow++);
	}

	/*
	 * Update the PTE as per "Adding a Page Table Entry". Lock is released
	 * by setting the high doubleworld.
	 */
	pt->pte_lo = htobe64(pvo_pt->pte_lo);
	EIEIO();
	pt->pte_hi = htobe64(pvo_pt->pte_hi);
	PTESYNC();

	/* Keep statistics */
	STAT_MOEA64(moea64_pte_valid++);

	return (k);
}