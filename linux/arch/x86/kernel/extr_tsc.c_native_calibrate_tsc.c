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
struct TYPE_2__ {scalar_t__ x86_vendor; int cpuid_level; scalar_t__ x86_model; } ;

/* Variables and functions */
 unsigned int HZ ; 
 scalar_t__ INTEL_FAM6_ATOM_GOLDMONT ; 
 scalar_t__ INTEL_FAM6_ATOM_GOLDMONT_D ; 
 int /*<<< orphan*/  X86_FEATURE_TSC_KNOWN_FREQ ; 
 int /*<<< orphan*/  X86_FEATURE_TSC_RELIABLE ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  cpuid (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 unsigned int lapic_timer_period ; 
 int /*<<< orphan*/  setup_force_cpu_cap (int /*<<< orphan*/ ) ; 

unsigned long native_calibrate_tsc(void)
{
	unsigned int eax_denominator, ebx_numerator, ecx_hz, edx;
	unsigned int crystal_khz;

	if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL)
		return 0;

	if (boot_cpu_data.cpuid_level < 0x15)
		return 0;

	eax_denominator = ebx_numerator = ecx_hz = edx = 0;

	/* CPUID 15H TSC/Crystal ratio, plus optionally Crystal Hz */
	cpuid(0x15, &eax_denominator, &ebx_numerator, &ecx_hz, &edx);

	if (ebx_numerator == 0 || eax_denominator == 0)
		return 0;

	crystal_khz = ecx_hz / 1000;

	/*
	 * Denverton SoCs don't report crystal clock, and also don't support
	 * CPUID.0x16 for the calculation below, so hardcode the 25MHz crystal
	 * clock.
	 */
	if (crystal_khz == 0 &&
			boot_cpu_data.x86_model == INTEL_FAM6_ATOM_GOLDMONT_D)
		crystal_khz = 25000;

	/*
	 * TSC frequency reported directly by CPUID is a "hardware reported"
	 * frequency and is the most accurate one so far we have. This
	 * is considered a known frequency.
	 */
	if (crystal_khz != 0)
		setup_force_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);

	/*
	 * Some Intel SoCs like Skylake and Kabylake don't report the crystal
	 * clock, but we can easily calculate it to a high degree of accuracy
	 * by considering the crystal ratio and the CPU speed.
	 */
	if (crystal_khz == 0 && boot_cpu_data.cpuid_level >= 0x16) {
		unsigned int eax_base_mhz, ebx, ecx, edx;

		cpuid(0x16, &eax_base_mhz, &ebx, &ecx, &edx);
		crystal_khz = eax_base_mhz * 1000 *
			eax_denominator / ebx_numerator;
	}

	if (crystal_khz == 0)
		return 0;

	/*
	 * For Atom SoCs TSC is the only reliable clocksource.
	 * Mark TSC reliable so no watchdog on it.
	 */
	if (boot_cpu_data.x86_model == INTEL_FAM6_ATOM_GOLDMONT)
		setup_force_cpu_cap(X86_FEATURE_TSC_RELIABLE);

#ifdef CONFIG_X86_LOCAL_APIC
	/*
	 * The local APIC appears to be fed by the core crystal clock
	 * (which sounds entirely sensible). We can set the global
	 * lapic_timer_period here to avoid having to calibrate the APIC
	 * timer later.
	 */
	lapic_timer_period = crystal_khz * 1000 / HZ;
#endif

	return crystal_khz * ebx_numerator / eax_denominator;
}