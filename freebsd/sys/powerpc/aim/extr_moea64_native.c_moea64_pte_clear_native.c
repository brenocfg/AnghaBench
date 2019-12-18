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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int slot; } ;
struct pvo_entry {int /*<<< orphan*/  pvo_vpn; int /*<<< orphan*/  pvo_pmap; TYPE_1__ pvo_pte; } ;
struct lpte {int pte_hi; int pte_lo; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int int64_t ;

/* Variables and functions */
 int LPTE_AVPN_MASK ; 
 int LPTE_CHG ; 
 int LPTE_REF ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTESYNC () ; 
 int /*<<< orphan*/  TLBIE (int /*<<< orphan*/ ) ; 
 int be64toh (int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  moea64_eviction_lock ; 
 int /*<<< orphan*/  moea64_pte_from_pvo (struct pvo_entry*,struct lpte*) ; 
 int /*<<< orphan*/  moea64_pte_insert_native (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int moea64_pte_unset_native (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 struct lpte* moea64_pteg_table ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t 
moea64_pte_clear_native(mmu_t mmu, struct pvo_entry *pvo, uint64_t ptebit)
{
	volatile struct lpte *pt = moea64_pteg_table + pvo->pvo_pte.slot;
	struct lpte properpt;
	uint64_t ptelo;

	PMAP_LOCK_ASSERT(pvo->pvo_pmap, MA_OWNED);

	moea64_pte_from_pvo(pvo, &properpt);

	rw_rlock(&moea64_eviction_lock);
	if ((be64toh(pt->pte_hi) & LPTE_AVPN_MASK) !=
	    (properpt.pte_hi & LPTE_AVPN_MASK)) {
		/* Evicted */
		rw_runlock(&moea64_eviction_lock);
		return (-1);
	}

	if (ptebit == LPTE_REF) {
		/* See "Resetting the Reference Bit" in arch manual */
		PTESYNC();
		/* 2-step here safe: precision is not guaranteed */
		ptelo = be64toh(pt->pte_lo);

		/* One-byte store to avoid touching the C bit */
		((volatile uint8_t *)(&pt->pte_lo))[6] =
#if BYTE_ORDER == BIG_ENDIAN
		    ((uint8_t *)(&properpt.pte_lo))[6];
#else
		    ((uint8_t *)(&properpt.pte_lo))[1];
#endif
		rw_runlock(&moea64_eviction_lock);

		critical_enter();
		TLBIE(pvo->pvo_vpn);
		critical_exit();
	} else {
		rw_runlock(&moea64_eviction_lock);
		ptelo = moea64_pte_unset_native(mmu, pvo);
		moea64_pte_insert_native(mmu, pvo);
	}

	return (ptelo & (LPTE_REF | LPTE_CHG));
}