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
 int CPUID_STEPPING ; 
 int CPUID_TSC ; 
#define  CPU_VENDOR_AMD 130 
#define  CPU_VENDOR_CENTAUR 129 
#define  CPU_VENDOR_NSC 128 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_FIRST ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cpu_feature ; 
 int cpu_id ; 
 int cpu_vendor_id ; 
 int /*<<< orphan*/  cpufreq_levels_changed ; 
 int /*<<< orphan*/  cpufreq_post_change ; 
 int /*<<< orphan*/  cpufreq_pre_change ; 
 int /*<<< orphan*/  probe_tsc_freq () ; 
 int /*<<< orphan*/  rdtsc ; 
 int /*<<< orphan*/  set_cputicker (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ tsc_disabled ; 
 scalar_t__ tsc_freq ; 
 int /*<<< orphan*/  tsc_freq_changed ; 
 int /*<<< orphan*/  tsc_freq_changing ; 
 scalar_t__ tsc_is_invariant ; 
 int /*<<< orphan*/  tsc_levels_changed ; 
 void* tsc_levels_tag ; 
 void* tsc_post_tag ; 
 void* tsc_pre_tag ; 

void
init_TSC(void)
{

	if ((cpu_feature & CPUID_TSC) == 0 || tsc_disabled)
		return;

#ifdef __i386__
	/* The TSC is known to be broken on certain CPUs. */
	switch (cpu_vendor_id) {
	case CPU_VENDOR_AMD:
		switch (cpu_id & 0xFF0) {
		case 0x500:
			/* K5 Model 0 */
			return;
		}
		break;
	case CPU_VENDOR_CENTAUR:
		switch (cpu_id & 0xff0) {
		case 0x540:
			/*
			 * http://www.centtech.com/c6_data_sheet.pdf
			 *
			 * I-12 RDTSC may return incoherent values in EDX:EAX
			 * I-13 RDTSC hangs when certain event counters are used
			 */
			return;
		}
		break;
	case CPU_VENDOR_NSC:
		switch (cpu_id & 0xff0) {
		case 0x540:
			if ((cpu_id & CPUID_STEPPING) == 0)
				return;
			break;
		}
		break;
	}
#endif
		
	probe_tsc_freq();

	/*
	 * Inform CPU accounting about our boot-time clock rate.  This will
	 * be updated if someone loads a cpufreq driver after boot that
	 * discovers a new max frequency.
	 */
	if (tsc_freq != 0)
		set_cputicker(rdtsc, tsc_freq, !tsc_is_invariant);

	if (tsc_is_invariant)
		return;

	/* Register to find out about changes in CPU frequency. */
	tsc_pre_tag = EVENTHANDLER_REGISTER(cpufreq_pre_change,
	    tsc_freq_changing, NULL, EVENTHANDLER_PRI_FIRST);
	tsc_post_tag = EVENTHANDLER_REGISTER(cpufreq_post_change,
	    tsc_freq_changed, NULL, EVENTHANDLER_PRI_FIRST);
	tsc_levels_tag = EVENTHANDLER_REGISTER(cpufreq_levels_changed,
	    tsc_levels_changed, NULL, EVENTHANDLER_PRI_ANY);
}