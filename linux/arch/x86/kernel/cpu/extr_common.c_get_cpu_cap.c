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
typedef  int u32 ;
struct cpuinfo_x86 {int cpuid_level; int* x86_capability; int extended_cpuid_level; int x86_power; } ;

/* Variables and functions */
 size_t CPUID_1_ECX ; 
 size_t CPUID_1_EDX ; 
 size_t CPUID_6_EAX ; 
 size_t CPUID_7_0_EBX ; 
 size_t CPUID_7_1_EAX ; 
 size_t CPUID_7_ECX ; 
 size_t CPUID_7_EDX ; 
 size_t CPUID_8000_0001_ECX ; 
 size_t CPUID_8000_0001_EDX ; 
 size_t CPUID_8000_0007_EBX ; 
 size_t CPUID_8000_0008_EBX ; 
 size_t CPUID_8000_000A_EDX ; 
 size_t CPUID_D_1_EAX ; 
 int /*<<< orphan*/  apply_forced_caps (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  cpuid (int,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  cpuid_count (int,int,int*,int*,int*,int*) ; 
 void* cpuid_eax (int) ; 
 int cpuid_edx (int) ; 
 int /*<<< orphan*/  init_cqm (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_scattered_cpuid_features (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_speculation_control (struct cpuinfo_x86*) ; 

void get_cpu_cap(struct cpuinfo_x86 *c)
{
	u32 eax, ebx, ecx, edx;

	/* Intel-defined flags: level 0x00000001 */
	if (c->cpuid_level >= 0x00000001) {
		cpuid(0x00000001, &eax, &ebx, &ecx, &edx);

		c->x86_capability[CPUID_1_ECX] = ecx;
		c->x86_capability[CPUID_1_EDX] = edx;
	}

	/* Thermal and Power Management Leaf: level 0x00000006 (eax) */
	if (c->cpuid_level >= 0x00000006)
		c->x86_capability[CPUID_6_EAX] = cpuid_eax(0x00000006);

	/* Additional Intel-defined flags: level 0x00000007 */
	if (c->cpuid_level >= 0x00000007) {
		cpuid_count(0x00000007, 0, &eax, &ebx, &ecx, &edx);
		c->x86_capability[CPUID_7_0_EBX] = ebx;
		c->x86_capability[CPUID_7_ECX] = ecx;
		c->x86_capability[CPUID_7_EDX] = edx;

		/* Check valid sub-leaf index before accessing it */
		if (eax >= 1) {
			cpuid_count(0x00000007, 1, &eax, &ebx, &ecx, &edx);
			c->x86_capability[CPUID_7_1_EAX] = eax;
		}
	}

	/* Extended state features: level 0x0000000d */
	if (c->cpuid_level >= 0x0000000d) {
		cpuid_count(0x0000000d, 1, &eax, &ebx, &ecx, &edx);

		c->x86_capability[CPUID_D_1_EAX] = eax;
	}

	/* AMD-defined flags: level 0x80000001 */
	eax = cpuid_eax(0x80000000);
	c->extended_cpuid_level = eax;

	if ((eax & 0xffff0000) == 0x80000000) {
		if (eax >= 0x80000001) {
			cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

			c->x86_capability[CPUID_8000_0001_ECX] = ecx;
			c->x86_capability[CPUID_8000_0001_EDX] = edx;
		}
	}

	if (c->extended_cpuid_level >= 0x80000007) {
		cpuid(0x80000007, &eax, &ebx, &ecx, &edx);

		c->x86_capability[CPUID_8000_0007_EBX] = ebx;
		c->x86_power = edx;
	}

	if (c->extended_cpuid_level >= 0x80000008) {
		cpuid(0x80000008, &eax, &ebx, &ecx, &edx);
		c->x86_capability[CPUID_8000_0008_EBX] = ebx;
	}

	if (c->extended_cpuid_level >= 0x8000000a)
		c->x86_capability[CPUID_8000_000A_EDX] = cpuid_edx(0x8000000a);

	init_scattered_cpuid_features(c);
	init_speculation_control(c);
	init_cqm(c);

	/*
	 * Clear/Set all flags overridden by options, after probe.
	 * This needs to happen each time we re-probe, which may happen
	 * several times during CPU initialization.
	 */
	apply_forced_caps(c);
}