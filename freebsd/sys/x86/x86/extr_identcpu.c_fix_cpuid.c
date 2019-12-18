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

/* Variables and functions */
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 int CPUID_TO_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_VENDOR_AMD ; 
 scalar_t__ CPU_VENDOR_INTEL ; 
 int IA32_MISC_EN_LIMCPUID ; 
 int /*<<< orphan*/  MSR_EXTFEATURES ; 
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 scalar_t__ VM_GUEST_NO ; 
 int /*<<< orphan*/  cpu_id ; 
 scalar_t__ cpu_vendor_id ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_guest ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

bool
fix_cpuid(void)
{
	uint64_t msr;

	/*
	 * Clear "Limit CPUID Maxval" bit and return true if the caller should
	 * get the largest standard CPUID function number again if it is set
	 * from BIOS.  It is necessary for probing correct CPU topology later
	 * and for the correct operation of the AVX-aware userspace.
	 */
	if (cpu_vendor_id == CPU_VENDOR_INTEL &&
	    ((CPUID_TO_FAMILY(cpu_id) == 0xf &&
	    CPUID_TO_MODEL(cpu_id) >= 0x3) ||
	    (CPUID_TO_FAMILY(cpu_id) == 0x6 &&
	    CPUID_TO_MODEL(cpu_id) >= 0xe))) {
		msr = rdmsr(MSR_IA32_MISC_ENABLE);
		if ((msr & IA32_MISC_EN_LIMCPUID) != 0) {
			msr &= ~IA32_MISC_EN_LIMCPUID;
			wrmsr(MSR_IA32_MISC_ENABLE, msr);
			return (true);
		}
	}

	/*
	 * Re-enable AMD Topology Extension that could be disabled by BIOS
	 * on some notebook processors.  Without the extension it's really
	 * hard to determine the correct CPU cache topology.
	 * See BIOS and Kernel Developer’s Guide (BKDG) for AMD Family 15h
	 * Models 60h-6Fh Processors, Publication # 50742.
	 */
	if (vm_guest == VM_GUEST_NO && cpu_vendor_id == CPU_VENDOR_AMD &&
	    CPUID_TO_FAMILY(cpu_id) == 0x15) {
		msr = rdmsr(MSR_EXTFEATURES);
		if ((msr & ((uint64_t)1 << 54)) == 0) {
			msr |= (uint64_t)1 << 54;
			wrmsr(MSR_EXTFEATURES, msr);
			return (true);
		}
	}
	return (false);
}