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
typedef  int u64 ;
typedef  unsigned int u32 ;
struct cpuinfo_x86 {int x86; int x86_model; int cpuid_level; int microcode; int x86_stepping; int x86_cache_alignment; int x86_phys_bits; int x86_power; int /*<<< orphan*/  x86_coreid_bits; } ;

/* Variables and functions */
#define  INTEL_FAM6_ATOM_AIRMONT_NP 131 
#define  INTEL_FAM6_ATOM_SALTWELL_MID 130 
#define  INTEL_FAM6_ATOM_SALTWELL_TABLET 129 
#define  INTEL_FAM6_ATOM_SILVERMONT_MID 128 
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 int MSR_IA32_MISC_ENABLE_FAST_STRING ; 
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE_LIMIT_CPUID_BIT ; 
 int /*<<< orphan*/  X86_FEATURE_CONSTANT_TSC ; 
 int /*<<< orphan*/  X86_FEATURE_ERMS ; 
 int /*<<< orphan*/  X86_FEATURE_IA64 ; 
 int /*<<< orphan*/  X86_FEATURE_IBPB ; 
 int /*<<< orphan*/  X86_FEATURE_IBRS ; 
 int /*<<< orphan*/  X86_FEATURE_INTEL_STIBP ; 
 int /*<<< orphan*/  X86_FEATURE_MSR_SPEC_CTRL ; 
 int /*<<< orphan*/  X86_FEATURE_NONSTOP_TSC ; 
 int /*<<< orphan*/  X86_FEATURE_NONSTOP_TSC_S3 ; 
 int /*<<< orphan*/  X86_FEATURE_PAT ; 
 int /*<<< orphan*/  X86_FEATURE_PGE ; 
 int /*<<< orphan*/  X86_FEATURE_PSE ; 
 int /*<<< orphan*/  X86_FEATURE_REP_GOOD ; 
 int /*<<< orphan*/  X86_FEATURE_SPEC_CTRL ; 
 int /*<<< orphan*/  X86_FEATURE_SPEC_CTRL_SSBD ; 
 int /*<<< orphan*/  X86_FEATURE_SSBD ; 
 int /*<<< orphan*/  X86_FEATURE_STIBP ; 
 int /*<<< orphan*/  X86_FEATURE_SYSENTER32 ; 
 scalar_t__ bad_spectre_microcode (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  check_memory_type_self_snoop_errata (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  check_mpx_erratum (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  clear_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int cpuid_eax (int /*<<< orphan*/ ) ; 
 scalar_t__ detect_extended_topology_early (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  detect_ht_early (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  get_count_order (unsigned int) ; 
 int /*<<< orphan*/  get_cpu_cap (struct cpuinfo_x86*) ; 
 int intel_get_microcode_revision () ; 
 scalar_t__ msr_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_clear_cpu_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void early_init_intel(struct cpuinfo_x86 *c)
{
	u64 misc_enable;

	/* Unmask CPUID levels if masked: */
	if (c->x86 > 6 || (c->x86 == 6 && c->x86_model >= 0xd)) {
		if (msr_clear_bit(MSR_IA32_MISC_ENABLE,
				  MSR_IA32_MISC_ENABLE_LIMIT_CPUID_BIT) > 0) {
			c->cpuid_level = cpuid_eax(0);
			get_cpu_cap(c);
		}
	}

	if ((c->x86 == 0xf && c->x86_model >= 0x03) ||
		(c->x86 == 0x6 && c->x86_model >= 0x0e))
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);

	if (c->x86 >= 6 && !cpu_has(c, X86_FEATURE_IA64))
		c->microcode = intel_get_microcode_revision();

	/* Now if any of them are set, check the blacklist and clear the lot */
	if ((cpu_has(c, X86_FEATURE_SPEC_CTRL) ||
	     cpu_has(c, X86_FEATURE_INTEL_STIBP) ||
	     cpu_has(c, X86_FEATURE_IBRS) || cpu_has(c, X86_FEATURE_IBPB) ||
	     cpu_has(c, X86_FEATURE_STIBP)) && bad_spectre_microcode(c)) {
		pr_warn("Intel Spectre v2 broken microcode detected; disabling Speculation Control\n");
		setup_clear_cpu_cap(X86_FEATURE_IBRS);
		setup_clear_cpu_cap(X86_FEATURE_IBPB);
		setup_clear_cpu_cap(X86_FEATURE_STIBP);
		setup_clear_cpu_cap(X86_FEATURE_SPEC_CTRL);
		setup_clear_cpu_cap(X86_FEATURE_MSR_SPEC_CTRL);
		setup_clear_cpu_cap(X86_FEATURE_INTEL_STIBP);
		setup_clear_cpu_cap(X86_FEATURE_SSBD);
		setup_clear_cpu_cap(X86_FEATURE_SPEC_CTRL_SSBD);
	}

	/*
	 * Atom erratum AAE44/AAF40/AAG38/AAH41:
	 *
	 * A race condition between speculative fetches and invalidating
	 * a large page.  This is worked around in microcode, but we
	 * need the microcode to have already been loaded... so if it is
	 * not, recommend a BIOS update and disable large pages.
	 */
	if (c->x86 == 6 && c->x86_model == 0x1c && c->x86_stepping <= 2 &&
	    c->microcode < 0x20e) {
		pr_warn("Atom PSE erratum detected, BIOS microcode update recommended\n");
		clear_cpu_cap(c, X86_FEATURE_PSE);
	}

#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_SYSENTER32);
#else
	/* Netburst reports 64 bytes clflush size, but does IO in 128 bytes */
	if (c->x86 == 15 && c->x86_cache_alignment == 64)
		c->x86_cache_alignment = 128;
#endif

	/* CPUID workaround for 0F33/0F34 CPU */
	if (c->x86 == 0xF && c->x86_model == 0x3
	    && (c->x86_stepping == 0x3 || c->x86_stepping == 0x4))
		c->x86_phys_bits = 36;

	/*
	 * c->x86_power is 8000_0007 edx. Bit 8 is TSC runs at constant rate
	 * with P/T states and does not stop in deep C-states.
	 *
	 * It is also reliable across cores and sockets. (but not across
	 * cabinets - we turn it off in that case explicitly.)
	 */
	if (c->x86_power & (1 << 8)) {
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC);
	}

	/* Penwell and Cloverview have the TSC which doesn't sleep on S3 */
	if (c->x86 == 6) {
		switch (c->x86_model) {
		case INTEL_FAM6_ATOM_SALTWELL_MID:
		case INTEL_FAM6_ATOM_SALTWELL_TABLET:
		case INTEL_FAM6_ATOM_SILVERMONT_MID:
		case INTEL_FAM6_ATOM_AIRMONT_NP:
			set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC_S3);
			break;
		default:
			break;
		}
	}

	/*
	 * There is a known erratum on Pentium III and Core Solo
	 * and Core Duo CPUs.
	 * " Page with PAT set to WC while associated MTRR is UC
	 *   may consolidate to UC "
	 * Because of this erratum, it is better to stick with
	 * setting WC in MTRR rather than using PAT on these CPUs.
	 *
	 * Enable PAT WC only on P4, Core 2 or later CPUs.
	 */
	if (c->x86 == 6 && c->x86_model < 15)
		clear_cpu_cap(c, X86_FEATURE_PAT);

	/*
	 * If fast string is not enabled in IA32_MISC_ENABLE for any reason,
	 * clear the fast string and enhanced fast string CPU capabilities.
	 */
	if (c->x86 > 6 || (c->x86 == 6 && c->x86_model >= 0xd)) {
		rdmsrl(MSR_IA32_MISC_ENABLE, misc_enable);
		if (!(misc_enable & MSR_IA32_MISC_ENABLE_FAST_STRING)) {
			pr_info("Disabled fast string operations\n");
			setup_clear_cpu_cap(X86_FEATURE_REP_GOOD);
			setup_clear_cpu_cap(X86_FEATURE_ERMS);
		}
	}

	/*
	 * Intel Quark Core DevMan_001.pdf section 6.4.11
	 * "The operating system also is required to invalidate (i.e., flush)
	 *  the TLB when any changes are made to any of the page table entries.
	 *  The operating system must reload CR3 to cause the TLB to be flushed"
	 *
	 * As a result, boot_cpu_has(X86_FEATURE_PGE) in arch/x86/include/asm/tlbflush.h
	 * should be false so that __flush_tlb_all() causes CR3 insted of CR4.PGE
	 * to be modified.
	 */
	if (c->x86 == 5 && c->x86_model == 9) {
		pr_info("Disabling PGE capability bit\n");
		setup_clear_cpu_cap(X86_FEATURE_PGE);
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

	check_mpx_erratum(c);
	check_memory_type_self_snoop_errata(c);

	/*
	 * Get the number of SMT siblings early from the extended topology
	 * leaf, if available. Otherwise try the legacy SMT detection.
	 */
	if (detect_extended_topology_early(c) < 0)
		detect_ht_early(c);
}