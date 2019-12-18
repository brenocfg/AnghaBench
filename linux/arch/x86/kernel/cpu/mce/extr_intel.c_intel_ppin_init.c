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
struct cpuinfo_x86 {int x86_model; } ;

/* Variables and functions */
#define  INTEL_FAM6_BROADWELL_D 134 
#define  INTEL_FAM6_BROADWELL_X 133 
#define  INTEL_FAM6_HASWELL_X 132 
#define  INTEL_FAM6_IVYBRIDGE_X 131 
#define  INTEL_FAM6_SKYLAKE_X 130 
#define  INTEL_FAM6_XEON_PHI_KNL 129 
#define  INTEL_FAM6_XEON_PHI_KNM 128 
 int /*<<< orphan*/  MSR_PPIN_CTL ; 
 int /*<<< orphan*/  X86_FEATURE_INTEL_PPIN ; 
 int /*<<< orphan*/  rdmsrl_safe (int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl_safe (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void intel_ppin_init(struct cpuinfo_x86 *c)
{
	unsigned long long val;

	/*
	 * Even if testing the presence of the MSR would be enough, we don't
	 * want to risk the situation where other models reuse this MSR for
	 * other purposes.
	 */
	switch (c->x86_model) {
	case INTEL_FAM6_IVYBRIDGE_X:
	case INTEL_FAM6_HASWELL_X:
	case INTEL_FAM6_BROADWELL_D:
	case INTEL_FAM6_BROADWELL_X:
	case INTEL_FAM6_SKYLAKE_X:
	case INTEL_FAM6_XEON_PHI_KNL:
	case INTEL_FAM6_XEON_PHI_KNM:

		if (rdmsrl_safe(MSR_PPIN_CTL, &val))
			return;

		if ((val & 3UL) == 1UL) {
			/* PPIN available but disabled: */
			return;
		}

		/* If PPIN is disabled, but not locked, try to enable: */
		if (!(val & 3UL)) {
			wrmsrl_safe(MSR_PPIN_CTL,  val | 2UL);
			rdmsrl_safe(MSR_PPIN_CTL, &val);
		}

		if ((val & 3UL) == 2UL)
			set_cpu_cap(c, X86_FEATURE_INTEL_PPIN);
	}
}