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
 int CPUID_STDEXT_HLE ; 
 int CPUID_STDEXT_RTM ; 
 int IA32_ARCH_CAP_TAA_NO ; 
 int IA32_ARCH_CAP_TSX_CTRL ; 
 int TAA_AUTO ; 
 int TAA_NONE ; 
 int TAA_TAA_NO ; 
 int TAA_TSX_DISABLE ; 
 int TAA_VERW ; 
 scalar_t__ bootverbose ; 
 int cpu_ia32_arch_caps ; 
 int cpu_stdext_feature ; 
 int hw_mds_disable ; 
 int /*<<< orphan*/  hw_mds_recalculate () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  taa_set (int,int) ; 
 int x86_taa_enable ; 
 int x86_taa_state ; 

void
x86_taa_recalculate(void)
{
	static int taa_saved_mds_disable = 0;
	int taa_need = 0, taa_state = 0;
	int mds_disable = 0, need_mds_recalc = 0;

	/* Check CPUID.07h.EBX.HLE and RTM for the presence of TSX */
	if ((cpu_stdext_feature & CPUID_STDEXT_HLE) == 0 ||
	    (cpu_stdext_feature & CPUID_STDEXT_RTM) == 0) {
		/* TSX is not present */
		x86_taa_state = 0;
		return;
	}

	/* Check to see what mitigation options the CPU gives us */
	if (cpu_ia32_arch_caps & IA32_ARCH_CAP_TAA_NO) {
		/* CPU is not suseptible to TAA */
		taa_need = TAA_NONE;
		taa_state = TAA_TAA_NO;
	} else if (cpu_ia32_arch_caps & IA32_ARCH_CAP_TSX_CTRL) {
		/*
		 * CPU can turn off TSX.  This is the next best option
		 * if TAA_NO hardware mitigation isn't present
		 */
		taa_need = TAA_TSX_DISABLE;
	} else {
		/* No TSX/TAA specific remedies are available. */
		if (x86_taa_enable == TAA_TSX_DISABLE) {
			if (bootverbose)
				printf("TSX control not available\n");
			return;
		} else
			taa_need = TAA_VERW;
	}

	/* Can we automatically take action, or are we being forced? */
	if (x86_taa_enable == TAA_AUTO)
		taa_state = taa_need;
	else
		taa_state = x86_taa_enable;

	/* No state change, nothing to do */
	if (taa_state == x86_taa_state) {
		if (bootverbose)
			printf("No TSX change made\n");
		return;
	}

	/* Does the MSR need to be turned on or off? */
	if (taa_state == TAA_TSX_DISABLE)
		taa_set(true, true);
	else if (x86_taa_state == TAA_TSX_DISABLE)
		taa_set(false, true);

	/* Does MDS need to be set to turn on VERW? */
	if (taa_state == TAA_VERW) {
		taa_saved_mds_disable = hw_mds_disable;
		mds_disable = hw_mds_disable = 1;
		need_mds_recalc = 1;
	} else if (x86_taa_state == TAA_VERW) {
		mds_disable = hw_mds_disable = taa_saved_mds_disable;
		need_mds_recalc = 1;
	}
	if (need_mds_recalc) {
		hw_mds_recalculate();
		if (mds_disable != hw_mds_disable) {
			if (bootverbose)
				printf("Cannot change MDS state for TAA\n");
			/* Don't update our state */
			return;
		}
	}

	x86_taa_state = taa_state;
	return;
}