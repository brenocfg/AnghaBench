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
struct cpuinfo_x86 {int x86; int x86_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_HWCAP2 ; 
 int /*<<< orphan*/  HWCAP2_RING3MWAIT ; 
#define  INTEL_FAM6_XEON_PHI_KNL 129 
#define  INTEL_FAM6_XEON_PHI_KNM 128 
 unsigned long MSR_MISC_FEATURES_ENABLES_RING3MWAIT_BIT ; 
 int /*<<< orphan*/  X86_FEATURE_RING3MWAIT ; 
 struct cpuinfo_x86 boot_cpu_data ; 
 int /*<<< orphan*/  msr_misc_features_shadow ; 
 scalar_t__ ring3mwait_disabled ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_or (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void probe_xeon_phi_r3mwait(struct cpuinfo_x86 *c)
{
	/*
	 * Ring 3 MONITOR/MWAIT feature cannot be detected without
	 * cpu model and family comparison.
	 */
	if (c->x86 != 6)
		return;
	switch (c->x86_model) {
	case INTEL_FAM6_XEON_PHI_KNL:
	case INTEL_FAM6_XEON_PHI_KNM:
		break;
	default:
		return;
	}

	if (ring3mwait_disabled)
		return;

	set_cpu_cap(c, X86_FEATURE_RING3MWAIT);
	this_cpu_or(msr_misc_features_shadow,
		    1UL << MSR_MISC_FEATURES_ENABLES_RING3MWAIT_BIT);

	if (c == &boot_cpu_data)
		ELF_HWCAP2 |= HWCAP2_RING3MWAIT;
}