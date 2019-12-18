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
typedef  unsigned int u32 ;
struct cpuinfo_x86 {int x86; int x86_power; int cpuid_level; int /*<<< orphan*/  x86_coreid_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_CONSTANT_TSC ; 
 int /*<<< orphan*/  X86_FEATURE_NONSTOP_TSC ; 
 int /*<<< orphan*/  X86_FEATURE_SYSENTER32 ; 
 int /*<<< orphan*/  cpuid (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  get_count_order (unsigned int) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void early_init_zhaoxin(struct cpuinfo_x86 *c)
{
	if (c->x86 >= 0x6)
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_SYSENTER32);
#endif
	if (c->x86_power & (1 << 8)) {
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC);
	}

	if (c->cpuid_level >= 0x00000001) {
		u32 eax, ebx, ecx, edx;

		cpuid(0x00000001, &eax, &ebx, &ecx, &edx);
		/*
		 * If HTT (EDX[28]) is set EBX[16:23] contain the number of
		 * apicids which are reserved per package. Store the resulting
		 * shift value for the package management code.
		 */
		if (edx & (1U << 28))
			c->x86_coreid_bits = get_count_order((ebx >> 16) & 0xff);
	}

}