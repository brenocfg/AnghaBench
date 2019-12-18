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
typedef  int sbintime_t ;

/* Variables and functions */
 int AMDK8_CMPHALT ; 
 int CPUID2_MON ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_SPARE2 ; 
 int /*<<< orphan*/  MSR_AMDK8_IPM ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_watchdog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_activeclock () ; 
 scalar_t__ cpu_disable_c3_sleep ; 
 int cpu_feature2 ; 
 scalar_t__ cpu_ident_amdc1e ; 
 int /*<<< orphan*/  cpu_idle_fn (int) ; 
 int /*<<< orphan*/  cpu_idle_mwait (int) ; 
 int cpu_idleclock () ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  curcpu ; 
 scalar_t__ idle_mwait ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

void
cpu_idle(int busy)
{
	uint64_t msr;
	sbintime_t sbt = -1;

	CTR2(KTR_SPARE2, "cpu_idle(%d) at %d",
	    busy, curcpu);
#ifdef MP_WATCHDOG
	ap_watchdog(PCPU_GET(cpuid));
#endif

	/* If we are busy - try to use fast methods. */
	if (busy) {
		if ((cpu_feature2 & CPUID2_MON) && idle_mwait) {
			cpu_idle_mwait(busy);
			goto out;
		}
	}

	/* If we have time - switch timers into idle mode. */
	if (!busy) {
		critical_enter();
		sbt = cpu_idleclock();
	}

	/* Apply AMD APIC timer C1E workaround. */
	if (cpu_ident_amdc1e && cpu_disable_c3_sleep) {
		msr = rdmsr(MSR_AMDK8_IPM);
		if (msr & AMDK8_CMPHALT)
			wrmsr(MSR_AMDK8_IPM, msr & ~AMDK8_CMPHALT);
	}

	/* Call main idle method. */
	cpu_idle_fn(sbt);

	/* Switch timers back into active mode. */
	if (!busy) {
		cpu_activeclock();
		critical_exit();
	}
out:
	CTR2(KTR_SPARE2, "cpu_idle(%d) at %d done",
	    busy, curcpu);
}