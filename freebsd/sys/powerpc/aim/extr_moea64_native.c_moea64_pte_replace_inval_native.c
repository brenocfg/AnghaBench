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
struct pvo_entry {int /*<<< orphan*/  pvo_vpn; } ;
struct lpte {int pte_hi; int pte_lo; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIEIO () ; 
 int LPTE_AVPN_MASK ; 
 int LPTE_CHG ; 
 int LPTE_LOCKED ; 
 int LPTE_REF ; 
 int LPTE_VALID ; 
 int /*<<< orphan*/  PTESYNC () ; 
 int /*<<< orphan*/  STAT_MOEA64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLBIE (int /*<<< orphan*/ ) ; 
 int be64toh (int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 void* htobe64 (int) ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  moea64_eviction_lock ; 
 int /*<<< orphan*/  moea64_pte_from_pvo (struct pvo_entry*,struct lpte*) ; 
 int /*<<< orphan*/  moea64_pte_overflow ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
moea64_pte_replace_inval_native(mmu_t mmu, struct pvo_entry *pvo,
    volatile struct lpte *pt)
{
	struct lpte properpt;
	uint64_t ptelo;

	moea64_pte_from_pvo(pvo, &properpt);

	rw_rlock(&moea64_eviction_lock);
	if ((be64toh(pt->pte_hi & LPTE_AVPN_MASK)) !=
	    (properpt.pte_hi & LPTE_AVPN_MASK)) {
		/* Evicted */
		STAT_MOEA64(moea64_pte_overflow--);
		rw_runlock(&moea64_eviction_lock);
		return (-1);
	}

	/*
	 * Replace the pte, briefly locking it to collect RC bits. No
	 * atomics needed since this is protected against eviction by the lock.
	 */
	isync();
	critical_enter();
	pt->pte_hi = be64toh((pt->pte_hi & ~LPTE_VALID) | LPTE_LOCKED);
	PTESYNC();
	TLBIE(pvo->pvo_vpn);
	ptelo = be64toh(pt->pte_lo);
	EIEIO();
	pt->pte_lo = htobe64(properpt.pte_lo);
	EIEIO();
	pt->pte_hi = htobe64(properpt.pte_hi); /* Release lock */
	PTESYNC();
	critical_exit();
	rw_runlock(&moea64_eviction_lock);

	return (ptelo & (LPTE_CHG | LPTE_REF));
}