#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int tc_quality; char* tc_name; int tc_frequency; void* tc_priv; int /*<<< orphan*/  tc_get_timecount; int /*<<< orphan*/  tc_flags; } ;

/* Variables and functions */
 int AMDPM_TSC_INVARIANT ; 
 int CPUID_SSE2 ; 
 int CPUID_TSC ; 
 scalar_t__ CPU_VENDOR_AMD ; 
 scalar_t__ CPU_VENDOR_INTEL ; 
 scalar_t__ POWER_PM_TYPE_APM ; 
 int /*<<< orphan*/  TC_FLAGS_C2STOP ; 
 int UINT_MAX ; 
 int amd_pminfo ; 
 scalar_t__ bootverbose ; 
 int cpu_feature ; 
 scalar_t__ cpu_vendor_id ; 
 int mp_ncpus ; 
 scalar_t__ power_pm_get_type () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  smp_tsc_adjust ; 
 int /*<<< orphan*/  tc_init (TYPE_1__*) ; 
 int test_tsc (int /*<<< orphan*/ ) ; 
 scalar_t__ tsc_disabled ; 
 int tsc_freq ; 
 int /*<<< orphan*/  tsc_get_timecount ; 
 int /*<<< orphan*/  tsc_get_timecount_lfence ; 
 int /*<<< orphan*/  tsc_get_timecount_low ; 
 int /*<<< orphan*/  tsc_get_timecount_low_lfence ; 
 int /*<<< orphan*/  tsc_get_timecount_low_mfence ; 
 int /*<<< orphan*/  tsc_get_timecount_mfence ; 
 scalar_t__ tsc_is_invariant ; 
 int tsc_shift ; 
 TYPE_1__ tsc_timecounter ; 

__attribute__((used)) static void
init_TSC_tc(void)
{
	uint64_t max_freq;
	int shift;

	if ((cpu_feature & CPUID_TSC) == 0 || tsc_disabled)
		return;

	/*
	 * Limit timecounter frequency to fit in an int and prevent it from
	 * overflowing too fast.
	 */
	max_freq = UINT_MAX;

	/*
	 * We can not use the TSC if we support APM.  Precise timekeeping
	 * on an APM'ed machine is at best a fools pursuit, since 
	 * any and all of the time spent in various SMM code can't 
	 * be reliably accounted for.  Reading the RTC is your only
	 * source of reliable time info.  The i8254 loses too, of course,
	 * but we need to have some kind of time...
	 * We don't know at this point whether APM is going to be used
	 * or not, nor when it might be activated.  Play it safe.
	 */
	if (power_pm_get_type() == POWER_PM_TYPE_APM) {
		tsc_timecounter.tc_quality = -1000;
		if (bootverbose)
			printf("TSC timecounter disabled: APM enabled.\n");
		goto init;
	}

	/*
	 * Intel CPUs without a C-state invariant TSC can stop the TSC
	 * in either C2 or C3.  Disable use of C2 and C3 while using
	 * the TSC as the timecounter.  The timecounter can be changed
	 * to enable C2 and C3.
	 *
	 * Note that the TSC is used as the cputicker for computing
	 * thread runtime regardless of the timecounter setting, so
	 * using an alternate timecounter and enabling C2 or C3 can
	 * result incorrect runtimes for kernel idle threads (but not
	 * for any non-idle threads).
	 */
	if (cpu_vendor_id == CPU_VENDOR_INTEL &&
	    (amd_pminfo & AMDPM_TSC_INVARIANT) == 0) {
		tsc_timecounter.tc_flags |= TC_FLAGS_C2STOP;
		if (bootverbose)
			printf("TSC timecounter disables C2 and C3.\n");
	}

	/*
	 * We can not use the TSC in SMP mode unless the TSCs on all CPUs
	 * are synchronized.  If the user is sure that the system has
	 * synchronized TSCs, set kern.timecounter.smp_tsc tunable to a
	 * non-zero value.  The TSC seems unreliable in virtualized SMP
	 * environments, so it is set to a negative quality in those cases.
	 */
#ifdef SMP
	if (mp_ncpus > 1)
		tsc_timecounter.tc_quality = test_tsc(smp_tsc_adjust);
	else
#endif /* SMP */
	if (tsc_is_invariant)
		tsc_timecounter.tc_quality = 1000;
	max_freq >>= tsc_shift;

init:
	for (shift = 0; shift <= 31 && (tsc_freq >> shift) > max_freq; shift++)
		;
	if ((cpu_feature & CPUID_SSE2) != 0 && mp_ncpus > 1) {
		if (cpu_vendor_id == CPU_VENDOR_AMD) {
			tsc_timecounter.tc_get_timecount = shift > 0 ?
			    tsc_get_timecount_low_mfence :
			    tsc_get_timecount_mfence;
		} else {
			tsc_timecounter.tc_get_timecount = shift > 0 ?
			    tsc_get_timecount_low_lfence :
			    tsc_get_timecount_lfence;
		}
	} else {
		tsc_timecounter.tc_get_timecount = shift > 0 ?
		    tsc_get_timecount_low : tsc_get_timecount;
	}
	if (shift > 0) {
		tsc_timecounter.tc_name = "TSC-low";
		if (bootverbose)
			printf("TSC timecounter discards lower %d bit(s)\n",
			    shift);
	}
	if (tsc_freq != 0) {
		tsc_timecounter.tc_frequency = tsc_freq >> shift;
		tsc_timecounter.tc_priv = (void *)(intptr_t)shift;
		tc_init(&tsc_timecounter);
	}
}