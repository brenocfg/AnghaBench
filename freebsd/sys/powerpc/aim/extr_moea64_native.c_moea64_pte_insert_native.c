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
struct TYPE_2__ {unsigned long long slot; } ;
struct pvo_entry {TYPE_1__ pvo_pte; int /*<<< orphan*/  pvo_vaddr; } ;
struct lpte {int /*<<< orphan*/  pte_hi; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  LPTE_HID ; 
 int LPTE_LOCKED ; 
 int LPTE_VALID ; 
 int LPTE_WIRED ; 
 int /*<<< orphan*/  PVO_HID ; 
 int /*<<< orphan*/  moea64_eviction_lock ; 
 uintptr_t moea64_insert_to_pteg_native (struct lpte*,unsigned long long,int) ; 
 int /*<<< orphan*/  moea64_pte_from_pvo (struct pvo_entry*,struct lpte*) ; 
 int moea64_pteg_mask ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_try_upgrade (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
moea64_pte_insert_native(mmu_t mmu, struct pvo_entry *pvo)
{
	struct lpte insertpt;
	uintptr_t slot;

	/* Initialize PTE */
	moea64_pte_from_pvo(pvo, &insertpt);

	/* Make sure further insertion is locked out during evictions */
	rw_rlock(&moea64_eviction_lock);

	/*
	 * First try primary hash.
	 */
	pvo->pvo_pte.slot &= ~7ULL; /* Base slot address */
	slot = moea64_insert_to_pteg_native(&insertpt, pvo->pvo_pte.slot,
	    LPTE_VALID | LPTE_WIRED | LPTE_LOCKED);
	if (slot != -1) {
		rw_runlock(&moea64_eviction_lock);
		pvo->pvo_pte.slot = slot;
		return (0);
	}

	/*
	 * Now try secondary hash.
	 */
	pvo->pvo_vaddr ^= PVO_HID;
	insertpt.pte_hi ^= LPTE_HID;
	pvo->pvo_pte.slot ^= (moea64_pteg_mask << 3);
	slot = moea64_insert_to_pteg_native(&insertpt, pvo->pvo_pte.slot,
	    LPTE_VALID | LPTE_WIRED | LPTE_LOCKED);
	if (slot != -1) {
		rw_runlock(&moea64_eviction_lock);
		pvo->pvo_pte.slot = slot;
		return (0);
	}

	/*
	 * Out of luck. Find a PTE to sacrifice.
	 */

	/* Lock out all insertions for a bit */
	if (!rw_try_upgrade(&moea64_eviction_lock)) {
		rw_runlock(&moea64_eviction_lock);
		rw_wlock(&moea64_eviction_lock);
	}

	slot = moea64_insert_to_pteg_native(&insertpt, pvo->pvo_pte.slot,
	    LPTE_WIRED | LPTE_LOCKED);
	if (slot != -1) {
		rw_wunlock(&moea64_eviction_lock);
		pvo->pvo_pte.slot = slot;
		return (0);
	}

	/* Try other hash table. Now we're getting desperate... */
	pvo->pvo_vaddr ^= PVO_HID;
	insertpt.pte_hi ^= LPTE_HID;
	pvo->pvo_pte.slot ^= (moea64_pteg_mask << 3);
	slot = moea64_insert_to_pteg_native(&insertpt, pvo->pvo_pte.slot,
	    LPTE_WIRED | LPTE_LOCKED);
	if (slot != -1) {
		rw_wunlock(&moea64_eviction_lock);
		pvo->pvo_pte.slot = slot;
		return (0);
	}

	/* No freeable slots in either PTEG? We're hosed. */
	rw_wunlock(&moea64_eviction_lock);
	panic("moea64_pte_insert: overflow");
	return (-1);
}