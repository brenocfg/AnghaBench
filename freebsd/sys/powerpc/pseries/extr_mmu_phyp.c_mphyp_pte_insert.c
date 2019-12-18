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
typedef  long uint64_t ;
struct rm_priotracker {int dummy; } ;
struct TYPE_2__ {unsigned long slot; } ;
struct pvo_entry {TYPE_1__ pvo_pte; int /*<<< orphan*/  pvo_vaddr; int /*<<< orphan*/  pvo_pmap; } ;
struct lpte {int pte_hi; long pte_lo; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  H_AVPN ; 
 int /*<<< orphan*/  H_ENTER ; 
 int /*<<< orphan*/  H_EXACT ; 
 scalar_t__ H_NOT_FOUND ; 
 scalar_t__ H_PTEG_FULL ; 
 int /*<<< orphan*/  H_REMOVE ; 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LPTE_AVPN_MASK ; 
 int LPTE_HID ; 
 int LPTE_VALID ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVO_HID ; 
 int /*<<< orphan*/  STAT_MOEA64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_pte_from_pvo (struct pvo_entry*,struct lpte*) ; 
 int /*<<< orphan*/  moea64_pte_overflow ; 
 int /*<<< orphan*/  moea64_pteg_count ; 
 int moea64_pteg_mask ; 
 int /*<<< orphan*/  mphyp_eviction_lock ; 
 long mphyp_pte_spillable_ident (long,struct lpte*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ phyp_pft_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int,long,long*,long*,long*) ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mphyp_pte_insert(mmu_t mmu, struct pvo_entry *pvo)
{
	struct rm_priotracker track;
	int64_t result;
	struct lpte evicted, pte;
	uint64_t index, junk, lastptelo;

	PMAP_LOCK_ASSERT(pvo->pvo_pmap, MA_OWNED);

	/* Initialize PTE */
	moea64_pte_from_pvo(pvo, &pte);
	evicted.pte_hi = 0;

	/* Make sure further insertion is locked out during evictions */
	rm_rlock(&mphyp_eviction_lock, &track);

	/*
	 * First try primary hash.
	 */
	pvo->pvo_pte.slot &= ~7UL; /* Base slot address */
	result = phyp_pft_hcall(H_ENTER, 0, pvo->pvo_pte.slot, pte.pte_hi,
	    pte.pte_lo, &index, &evicted.pte_lo, &junk);
	if (result == H_SUCCESS) {
		rm_runlock(&mphyp_eviction_lock, &track);
		pvo->pvo_pte.slot = index;
		return (0);
	}
	KASSERT(result == H_PTEG_FULL, ("Page insertion error: %ld "
	    "(ptegidx: %#zx/%#lx, PTE %#lx/%#lx", result, pvo->pvo_pte.slot,
	    moea64_pteg_count, pte.pte_hi, pte.pte_lo));

	/*
	 * Next try secondary hash.
	 */
	pvo->pvo_vaddr ^= PVO_HID;
	pte.pte_hi ^= LPTE_HID;
	pvo->pvo_pte.slot ^= (moea64_pteg_mask << 3);

	result = phyp_pft_hcall(H_ENTER, 0, pvo->pvo_pte.slot,
	    pte.pte_hi, pte.pte_lo, &index, &evicted.pte_lo, &junk);
	if (result == H_SUCCESS) {
		rm_runlock(&mphyp_eviction_lock, &track);
		pvo->pvo_pte.slot = index;
		return (0);
	}
	KASSERT(result == H_PTEG_FULL, ("Secondary page insertion error: %ld",
	    result));

	/*
	 * Out of luck. Find a PTE to sacrifice.
	 */

	/* Lock out all insertions for a bit */
	rm_runlock(&mphyp_eviction_lock, &track);
	rm_wlock(&mphyp_eviction_lock);

	index = mphyp_pte_spillable_ident(pvo->pvo_pte.slot, &evicted);
	if (index == -1L) {
		/* Try other hash table? */
		pvo->pvo_vaddr ^= PVO_HID;
		pte.pte_hi ^= LPTE_HID;
		pvo->pvo_pte.slot ^= (moea64_pteg_mask << 3);
		index = mphyp_pte_spillable_ident(pvo->pvo_pte.slot, &evicted);
	}

	if (index == -1L) {
		/* No freeable slots in either PTEG? We're hosed. */
		rm_wunlock(&mphyp_eviction_lock);
		panic("mphyp_pte_insert: overflow");
		return (-1);
	}

	/* Victim acquired: update page before waving goodbye */
	if (evicted.pte_hi & LPTE_VALID) {
		result = phyp_pft_hcall(H_REMOVE, H_AVPN, index,
		    evicted.pte_hi & LPTE_AVPN_MASK, 0, &junk, &lastptelo,
		    &junk);
		STAT_MOEA64(moea64_pte_overflow++);
		KASSERT(result == H_SUCCESS || result == H_NOT_FOUND,
		    ("Error evicting page: %d", (int)result));
	}

	/*
	 * Set the new PTE.
	 */
	result = phyp_pft_hcall(H_ENTER, H_EXACT, index, pte.pte_hi,
	    pte.pte_lo, &index, &evicted.pte_lo, &junk);
	rm_wunlock(&mphyp_eviction_lock); /* All clear */

	pvo->pvo_pte.slot = index;
	if (result == H_SUCCESS)
		return (0);

	panic("Page replacement error: %ld", result);
	return (result);
}