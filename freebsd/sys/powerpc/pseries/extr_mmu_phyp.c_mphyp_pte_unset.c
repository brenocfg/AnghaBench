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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  slot; } ;
struct pvo_entry {TYPE_1__ pvo_pte; int /*<<< orphan*/  pvo_pmap; } ;
struct lpte {int pte_hi; int pte_lo; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  H_AVPN ; 
 int H_NOT_FOUND ; 
 int /*<<< orphan*/  H_REMOVE ; 
 int H_SUCCESS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LPTE_AVPN_MASK ; 
 int LPTE_CHG ; 
 int LPTE_REF ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAT_MOEA64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_pte_from_pvo (struct pvo_entry*,struct lpte*) ; 
 int /*<<< orphan*/  moea64_pte_overflow ; 
 int phyp_pft_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
mphyp_pte_unset(mmu_t mmu, struct pvo_entry *pvo)
{
	struct lpte pte;
	uint64_t junk;
	int err;

	PMAP_LOCK_ASSERT(pvo->pvo_pmap, MA_OWNED);

	moea64_pte_from_pvo(pvo, &pte);

	err = phyp_pft_hcall(H_REMOVE, H_AVPN, pvo->pvo_pte.slot,
	    pte.pte_hi & LPTE_AVPN_MASK, 0, &pte.pte_hi, &pte.pte_lo,
	    &junk);
	KASSERT(err == H_SUCCESS || err == H_NOT_FOUND,
	    ("Error removing page: %d", err));

	if (err == H_NOT_FOUND) {
		STAT_MOEA64(moea64_pte_overflow--);
		return (-1);
	}

	return (pte.pte_lo & (LPTE_REF | LPTE_CHG));
}