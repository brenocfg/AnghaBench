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
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int CPUID_TSC ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MSR_APERF ; 
 int /*<<< orphan*/  MSR_MPERF ; 
 int cpu_feature ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcpu_find (int) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int rdtsc () ; 
 int /*<<< orphan*/  sched_bind (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sched_unbind (int /*<<< orphan*/ ) ; 
 int smp_cpus ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ tsc_is_invariant ; 
 int /*<<< orphan*/  tsc_perf_stat ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cpu_est_clockrate(int cpu_id, uint64_t *rate)
{
	uint64_t tsc1, tsc2;
	uint64_t acnt, mcnt, perf;
	register_t reg;

	if (pcpu_find(cpu_id) == NULL || rate == NULL)
		return (EINVAL);
#ifdef __i386__
	if ((cpu_feature & CPUID_TSC) == 0)
		return (EOPNOTSUPP);
#endif

	/*
	 * If TSC is P-state invariant and APERF/MPERF MSRs do not exist,
	 * DELAY(9) based logic fails.
	 */
	if (tsc_is_invariant && !tsc_perf_stat)
		return (EOPNOTSUPP);

#ifdef SMP
	if (smp_cpus > 1) {
		/* Schedule ourselves on the indicated cpu. */
		thread_lock(curthread);
		sched_bind(curthread, cpu_id);
		thread_unlock(curthread);
	}
#endif

	/* Calibrate by measuring a short delay. */
	reg = intr_disable();
	if (tsc_is_invariant) {
		wrmsr(MSR_MPERF, 0);
		wrmsr(MSR_APERF, 0);
		tsc1 = rdtsc();
		DELAY(1000);
		mcnt = rdmsr(MSR_MPERF);
		acnt = rdmsr(MSR_APERF);
		tsc2 = rdtsc();
		intr_restore(reg);
		perf = 1000 * acnt / mcnt;
		*rate = (tsc2 - tsc1) * perf;
	} else {
		tsc1 = rdtsc();
		DELAY(1000);
		tsc2 = rdtsc();
		intr_restore(reg);
		*rate = (tsc2 - tsc1) * 1000;
	}

#ifdef SMP
	if (smp_cpus > 1) {
		thread_lock(curthread);
		sched_unbind(curthread);
		thread_unlock(curthread);
	}
#endif

	return (0);
}