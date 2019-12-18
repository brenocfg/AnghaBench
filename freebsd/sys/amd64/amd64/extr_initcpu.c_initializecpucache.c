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

/* Variables and functions */
 int CPUID_CLFSH ; 
 int /*<<< orphan*/  CPUID_STDEXT_CLFLUSHOPT ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 scalar_t__ VM_GUEST_NO ; 
 int cpu_clflush_line_size ; 
 int cpu_feature ; 
 int cpu_procinfo ; 
 int /*<<< orphan*/  cpu_stdext_feature ; 
 int hw_clflush_disable ; 
 scalar_t__ vm_guest ; 

void
initializecpucache(void)
{

	/*
	 * CPUID with %eax = 1, %ebx returns
	 * Bits 15-8: CLFLUSH line size
	 * 	(Value * 8 = cache line size in bytes)
	 */
	if ((cpu_feature & CPUID_CLFSH) != 0)
		cpu_clflush_line_size = ((cpu_procinfo >> 8) & 0xff) * 8;
	/*
	 * XXXKIB: (temporary) hack to work around traps generated
	 * when CLFLUSHing APIC register window under virtualization
	 * environments.  These environments tend to disable the
	 * CPUID_SS feature even though the native CPU supports it.
	 */
	TUNABLE_INT_FETCH("hw.clflush_disable", &hw_clflush_disable);
	if (vm_guest != VM_GUEST_NO && hw_clflush_disable == -1) {
		cpu_feature &= ~CPUID_CLFSH;
		cpu_stdext_feature &= ~CPUID_STDEXT_CLFLUSHOPT;
	}

	/*
	 * The kernel's use of CLFLUSH{,OPT} can be disabled manually
	 * by setting the hw.clflush_disable tunable.
	 */
	if (hw_clflush_disable == 1) {
		cpu_feature &= ~CPUID_CLFSH;
		cpu_stdext_feature &= ~CPUID_STDEXT_CLFLUSHOPT;
	}
}