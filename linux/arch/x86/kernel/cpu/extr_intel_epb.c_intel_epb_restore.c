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
typedef  int u64 ;

/* Variables and functions */
 int ENERGY_PERF_BIAS_NORMAL ; 
 int ENERGY_PERF_BIAS_PERFORMANCE ; 
 int EPB_MASK ; 
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saved_epb ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intel_epb_restore(void)
{
	u64 val = this_cpu_read(saved_epb);
	u64 epb;

	rdmsrl(MSR_IA32_ENERGY_PERF_BIAS, epb);
	if (val) {
		val &= EPB_MASK;
	} else {
		/*
		 * Because intel_epb_save() has not run for the current CPU yet,
		 * it is going online for the first time, so if its EPB value is
		 * 0 ('performance') at this point, assume that it has not been
		 * initialized by the platform firmware and set it to 6
		 * ('normal').
		 */
		val = epb & EPB_MASK;
		if (val == ENERGY_PERF_BIAS_PERFORMANCE) {
			val = ENERGY_PERF_BIAS_NORMAL;
			pr_warn_once("ENERGY_PERF_BIAS: Set to 'normal', was 'performance'\n");
		}
	}
	wrmsrl(MSR_IA32_ENERGY_PERF_BIAS, (epb & ~EPB_MASK) | val);
}