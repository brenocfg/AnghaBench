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
 int /*<<< orphan*/  H_TLBIE_P1_ENC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  H_TLB_INVALIDATE ; 
 int /*<<< orphan*/  TLBIEL_INVAL_SET_LPID ; 
 int /*<<< orphan*/  kvmhv_on_pseries () ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,long) ; 
 int /*<<< orphan*/  radix__flush_all_lpid (unsigned int) ; 

__attribute__((used)) static void kvmhv_flush_lpid(unsigned int lpid)
{
	long rc;

	if (!kvmhv_on_pseries()) {
		radix__flush_all_lpid(lpid);
		return;
	}

	rc = plpar_hcall_norets(H_TLB_INVALIDATE, H_TLBIE_P1_ENC(2, 0, 1),
				lpid, TLBIEL_INVAL_SET_LPID);
	if (rc)
		pr_err("KVM: TLB LPID invalidation hcall failed, rc=%ld\n", rc);
}