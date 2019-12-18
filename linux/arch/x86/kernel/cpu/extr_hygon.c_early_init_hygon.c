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
typedef  int /*<<< orphan*/  u32 ;
struct cpuinfo_x86 {int x86_power; int /*<<< orphan*/  microcode; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MSR_AMD64_PATCH_LEVEL ; 
 int /*<<< orphan*/  X86_FEATURE_ACC_POWER ; 
 int /*<<< orphan*/  X86_FEATURE_APIC ; 
 int /*<<< orphan*/  X86_FEATURE_CONSTANT_TSC ; 
 int /*<<< orphan*/  X86_FEATURE_EXTD_APICID ; 
 int /*<<< orphan*/  X86_FEATURE_K8 ; 
 int /*<<< orphan*/  X86_FEATURE_NONSTOP_TSC ; 
 int /*<<< orphan*/  X86_FEATURE_SYSCALL32 ; 
 int /*<<< orphan*/  X86_FEATURE_VMMCALL ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  early_init_hygon_mc (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  hygon_get_topology_early (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  rdmsr_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void early_init_hygon(struct cpuinfo_x86 *c)
{
	u32 dummy;

	early_init_hygon_mc(c);

	set_cpu_cap(c, X86_FEATURE_K8);

	rdmsr_safe(MSR_AMD64_PATCH_LEVEL, &c->microcode, &dummy);

	/*
	 * c->x86_power is 8000_0007 edx. Bit 8 is TSC runs at constant rate
	 * with P/T states and does not stop in deep C-states
	 */
	if (c->x86_power & (1 << 8)) {
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC);
	}

	/* Bit 12 of 8000_0007 edx is accumulated power mechanism. */
	if (c->x86_power & BIT(12))
		set_cpu_cap(c, X86_FEATURE_ACC_POWER);

#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_SYSCALL32);
#endif

#if defined(CONFIG_X86_LOCAL_APIC) && defined(CONFIG_PCI)
	/*
	 * ApicID can always be treated as an 8-bit value for Hygon APIC So, we
	 * can safely set X86_FEATURE_EXTD_APICID unconditionally.
	 */
	if (boot_cpu_has(X86_FEATURE_APIC))
		set_cpu_cap(c, X86_FEATURE_EXTD_APICID);
#endif

	/*
	 * This is only needed to tell the kernel whether to use VMCALL
	 * and VMMCALL.  VMMCALL is never executed except under virt, so
	 * we can set it unconditionally.
	 */
	set_cpu_cap(c, X86_FEATURE_VMMCALL);

	hygon_get_topology_early(c);
}