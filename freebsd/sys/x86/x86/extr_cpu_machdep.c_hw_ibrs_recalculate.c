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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int CPUID_STDEXT3_IBPB ; 
 int IA32_ARCH_CAP_IBRS_ALL ; 
 scalar_t__ IA32_SPEC_CTRL_IBRS ; 
 int /*<<< orphan*/  MSR_IA32_SPEC_CTRL ; 
 int cpu_ia32_arch_caps ; 
 int cpu_stdext_feature3 ; 
 int hw_ibrs_active ; 
 scalar_t__ hw_ibrs_disable ; 
 scalar_t__ rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,scalar_t__) ; 

void
hw_ibrs_recalculate(void)
{
	uint64_t v;

	if ((cpu_ia32_arch_caps & IA32_ARCH_CAP_IBRS_ALL) != 0) {
		if (hw_ibrs_disable) {
			v = rdmsr(MSR_IA32_SPEC_CTRL);
			v &= ~(uint64_t)IA32_SPEC_CTRL_IBRS;
			wrmsr(MSR_IA32_SPEC_CTRL, v);
		} else {
			v = rdmsr(MSR_IA32_SPEC_CTRL);
			v |= IA32_SPEC_CTRL_IBRS;
			wrmsr(MSR_IA32_SPEC_CTRL, v);
		}
		return;
	}
	hw_ibrs_active = (cpu_stdext_feature3 & CPUID_STDEXT3_IBPB) != 0 &&
	    !hw_ibrs_disable;
}