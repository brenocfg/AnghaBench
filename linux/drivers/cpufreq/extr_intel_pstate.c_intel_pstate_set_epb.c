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
typedef  int s16 ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 int /*<<< orphan*/  X86_FEATURE_EPB ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int rdmsrl_on_cpu (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wrmsrl_on_cpu (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int intel_pstate_set_epb(int cpu, s16 pref)
{
	u64 epb;
	int ret;

	if (!boot_cpu_has(X86_FEATURE_EPB))
		return -ENXIO;

	ret = rdmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS, &epb);
	if (ret)
		return ret;

	epb = (epb & ~0x0f) | pref;
	wrmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS, epb);

	return 0;
}