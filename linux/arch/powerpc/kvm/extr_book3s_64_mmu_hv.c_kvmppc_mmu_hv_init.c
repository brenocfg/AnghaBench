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

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int EINVAL ; 
 unsigned long LPID_RSVD ; 
 int /*<<< orphan*/  MMU_FTR_LOCKLESS_TLBIE ; 
 int /*<<< orphan*/  SPRN_LPID ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_claim_lpid (unsigned long) ; 
 int /*<<< orphan*/  kvmppc_init_lpid (unsigned long) ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_has_feature (int /*<<< orphan*/ ) ; 

int kvmppc_mmu_hv_init(void)
{
	unsigned long host_lpid, rsvd_lpid;

	if (!mmu_has_feature(MMU_FTR_LOCKLESS_TLBIE))
		return -EINVAL;

	/* POWER7 has 10-bit LPIDs (12-bit in POWER8) */
	host_lpid = 0;
	if (cpu_has_feature(CPU_FTR_HVMODE))
		host_lpid = mfspr(SPRN_LPID);
	rsvd_lpid = LPID_RSVD;

	kvmppc_init_lpid(rsvd_lpid + 1);

	kvmppc_claim_lpid(host_lpid);
	/* rsvd_lpid is reserved for use in partition switching */
	kvmppc_claim_lpid(rsvd_lpid);

	return 0;
}