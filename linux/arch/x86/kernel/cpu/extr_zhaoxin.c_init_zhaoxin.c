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
struct cpuinfo_x86 {int cpuid_level; int x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_ARCH_PERFMON ; 
 int /*<<< orphan*/  X86_FEATURE_LFENCE_RDTSC ; 
 int /*<<< orphan*/  X86_FEATURE_VMX ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 unsigned int cpuid_eax (int) ; 
 int /*<<< orphan*/  detect_ht (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  detect_num_cpu_cores (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  early_init_zhaoxin (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_intel_cacheinfo (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_zhaoxin_cap (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zhaoxin_detect_vmx_virtcap (struct cpuinfo_x86*) ; 

__attribute__((used)) static void init_zhaoxin(struct cpuinfo_x86 *c)
{
	early_init_zhaoxin(c);
	init_intel_cacheinfo(c);
	detect_num_cpu_cores(c);
#ifdef CONFIG_X86_32
	detect_ht(c);
#endif

	if (c->cpuid_level > 9) {
		unsigned int eax = cpuid_eax(10);

		/*
		 * Check for version and the number of counters
		 * Version(eax[7:0]) can't be 0;
		 * Counters(eax[15:8]) should be greater than 1;
		 */
		if ((eax & 0xff) && (((eax >> 8) & 0xff) > 1))
			set_cpu_cap(c, X86_FEATURE_ARCH_PERFMON);
	}

	if (c->x86 >= 0x6)
		init_zhaoxin_cap(c);
#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_LFENCE_RDTSC);
#endif

	if (cpu_has(c, X86_FEATURE_VMX))
		zhaoxin_detect_vmx_virtcap(c);
}