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
 int /*<<< orphan*/  SEC_FTR_BNDS_CHK_SPEC_BAR ; 
 int /*<<< orphan*/  SEC_FTR_FAVOUR_SECURITY ; 
 int /*<<< orphan*/  cpu_mitigations_off () ; 
 int /*<<< orphan*/  enable_barrier_nospec (int) ; 
 int /*<<< orphan*/  no_nospec ; 
 scalar_t__ security_ftr_enabled (int /*<<< orphan*/ ) ; 

void setup_barrier_nospec(void)
{
	bool enable;

	/*
	 * It would make sense to check SEC_FTR_SPEC_BAR_ORI31 below as well.
	 * But there's a good reason not to. The two flags we check below are
	 * both are enabled by default in the kernel, so if the hcall is not
	 * functional they will be enabled.
	 * On a system where the host firmware has been updated (so the ori
	 * functions as a barrier), but on which the hypervisor (KVM/Qemu) has
	 * not been updated, we would like to enable the barrier. Dropping the
	 * check for SEC_FTR_SPEC_BAR_ORI31 achieves that. The only downside is
	 * we potentially enable the barrier on systems where the host firmware
	 * is not updated, but that's harmless as it's a no-op.
	 */
	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) &&
		 security_ftr_enabled(SEC_FTR_BNDS_CHK_SPEC_BAR);

	if (!no_nospec && !cpu_mitigations_off())
		enable_barrier_nospec(enable);
}