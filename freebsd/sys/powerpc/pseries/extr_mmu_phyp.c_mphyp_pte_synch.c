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
struct pvo_entry {int pvo_vpn; TYPE_1__ pvo_pte; } ;
struct lpte {int pte_hi; int pte_lo; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int int64_t ;

/* Variables and functions */
 int ADDR_API_SHFT64 ; 
 int ADDR_PIDX_SHFT ; 
 int /*<<< orphan*/  H_READ ; 
 int LPTE_AVPN_MASK ; 
 int LPTE_CHG ; 
 int LPTE_REF ; 
 int LPTE_VALID ; 
 int /*<<< orphan*/  phyp_pft_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
mphyp_pte_synch(mmu_t mmu, struct pvo_entry *pvo)
{
	struct lpte pte;
	uint64_t junk;

	__asm __volatile("ptesync");
	phyp_pft_hcall(H_READ, 0, pvo->pvo_pte.slot, 0, 0, &pte.pte_hi,
	    &pte.pte_lo, &junk);
	if ((pte.pte_hi & LPTE_AVPN_MASK) !=
	    ((pvo->pvo_vpn >> (ADDR_API_SHFT64 - ADDR_PIDX_SHFT)) &
	    LPTE_AVPN_MASK))
		return (-1);
	if (!(pte.pte_hi & LPTE_VALID))
		return (-1);

	return (pte.pte_lo & (LPTE_CHG | LPTE_REF));
}