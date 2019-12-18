#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int x86_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 int MSR_IA32_MISC_ENABLE_TURBO_DISABLE ; 
 int /*<<< orphan*/  MSR_K7_HWCR ; 
 int MSR_K7_HWCR_CPB_DIS ; 
#define  X86_VENDOR_AMD 130 
#define  X86_VENDOR_HYGON 129 
#define  X86_VENDOR_INTEL 128 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  rdmsr_on_cpu (unsigned int,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static bool boost_state(unsigned int cpu)
{
	u32 lo, hi;
	u64 msr;

	switch (boot_cpu_data.x86_vendor) {
	case X86_VENDOR_INTEL:
		rdmsr_on_cpu(cpu, MSR_IA32_MISC_ENABLE, &lo, &hi);
		msr = lo | ((u64)hi << 32);
		return !(msr & MSR_IA32_MISC_ENABLE_TURBO_DISABLE);
	case X86_VENDOR_HYGON:
	case X86_VENDOR_AMD:
		rdmsr_on_cpu(cpu, MSR_K7_HWCR, &lo, &hi);
		msr = lo | ((u64)hi << 32);
		return !(msr & MSR_K7_HWCR_CPB_DIS);
	}
	return false;
}