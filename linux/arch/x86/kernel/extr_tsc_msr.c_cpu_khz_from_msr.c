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
typedef  int u32 ;
struct x86_cpu_id {scalar_t__ driver_data; } ;
struct freq_desc {int* freqs; scalar_t__ msr_plat; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MSR_FSB_FREQ ; 
 int /*<<< orphan*/  MSR_IA32_PERF_STATUS ; 
 int /*<<< orphan*/  MSR_PLATFORM_INFO ; 
 int /*<<< orphan*/  X86_FEATURE_TSC_KNOWN_FREQ ; 
 int /*<<< orphan*/  X86_FEATURE_TSC_RELIABLE ; 
 int lapic_timer_period ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  setup_force_cpu_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc_msr_cpu_ids ; 
 struct x86_cpu_id* x86_match_cpu (int /*<<< orphan*/ ) ; 

unsigned long cpu_khz_from_msr(void)
{
	u32 lo, hi, ratio, freq;
	const struct freq_desc *freq_desc;
	const struct x86_cpu_id *id;
	unsigned long res;

	id = x86_match_cpu(tsc_msr_cpu_ids);
	if (!id)
		return 0;

	freq_desc = (struct freq_desc *)id->driver_data;
	if (freq_desc->msr_plat) {
		rdmsr(MSR_PLATFORM_INFO, lo, hi);
		ratio = (lo >> 8) & 0xff;
	} else {
		rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
		ratio = (hi >> 8) & 0x1f;
	}

	/* Get FSB FREQ ID */
	rdmsr(MSR_FSB_FREQ, lo, hi);

	/* Map CPU reference clock freq ID(0-7) to CPU reference clock freq(KHz) */
	freq = freq_desc->freqs[lo & 0x7];

	/* TSC frequency = maximum resolved freq * maximum resolved bus ratio */
	res = freq * ratio;

#ifdef CONFIG_X86_LOCAL_APIC
	lapic_timer_period = (freq * 1000) / HZ;
#endif

	/*
	 * TSC frequency determined by MSR is always considered "known"
	 * because it is reported by HW.
	 * Another fact is that on MSR capable platforms, PIT/HPET is
	 * generally not available so calibration won't work at all.
	 */
	setup_force_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);

	/*
	 * Unfortunately there is no way for hardware to tell whether the
	 * TSC is reliable.  We were told by silicon design team that TSC
	 * on Atom SoCs are always "reliable". TSC is also the only
	 * reliable clocksource on these SoCs (HPET is either not present
	 * or not functional) so mark TSC reliable which removes the
	 * requirement for a watchdog clocksource.
	 */
	setup_force_cpu_cap(X86_FEATURE_TSC_RELIABLE);

	return res;
}