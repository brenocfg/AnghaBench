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
struct cpuinfo_x86 {int /*<<< orphan*/  apicid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_F10H_DECFG ; 
 int /*<<< orphan*/  MSR_F10H_DECFG_LFENCE_SERIALIZE_BIT ; 
 int /*<<< orphan*/  X86_BUG_SYSRET_SS_ATTRS ; 
 int /*<<< orphan*/  X86_FEATURE_ARAT ; 
 int /*<<< orphan*/  X86_FEATURE_CPB ; 
 int /*<<< orphan*/  X86_FEATURE_LFENCE_RDTSC ; 
 int /*<<< orphan*/  X86_FEATURE_REP_GOOD ; 
 int /*<<< orphan*/  X86_FEATURE_XENPV ; 
 int /*<<< orphan*/  X86_FEATURE_XMM2 ; 
 int /*<<< orphan*/  X86_FEATURE_ZEN ; 
 int /*<<< orphan*/  clear_cpu_cap (struct cpuinfo_x86*,int) ; 
 int /*<<< orphan*/  cpu_detect_cache_sizes (struct cpuinfo_x86*) ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  early_init_hygon (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  hard_smp_processor_id () ; 
 int /*<<< orphan*/  hygon_detect_cmp (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  hygon_get_topology (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_hygon_cacheinfo (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  msr_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_bug (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srat_detect_node (struct cpuinfo_x86*) ; 

__attribute__((used)) static void init_hygon(struct cpuinfo_x86 *c)
{
	early_init_hygon(c);

	/*
	 * Bit 31 in normal CPUID used for nonstandard 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	clear_cpu_cap(c, 0*32+31);

	set_cpu_cap(c, X86_FEATURE_REP_GOOD);

	/* get apicid instead of initial apic id from cpuid */
	c->apicid = hard_smp_processor_id();

	set_cpu_cap(c, X86_FEATURE_ZEN);
	set_cpu_cap(c, X86_FEATURE_CPB);

	cpu_detect_cache_sizes(c);

	hygon_detect_cmp(c);
	hygon_get_topology(c);
	srat_detect_node(c);

	init_hygon_cacheinfo(c);

	if (cpu_has(c, X86_FEATURE_XMM2)) {
		/*
		 * Use LFENCE for execution serialization.  On families which
		 * don't have that MSR, LFENCE is already serializing.
		 * msr_set_bit() uses the safe accessors, too, even if the MSR
		 * is not present.
		 */
		msr_set_bit(MSR_F10H_DECFG,
			    MSR_F10H_DECFG_LFENCE_SERIALIZE_BIT);

		/* A serializing LFENCE stops RDTSC speculation */
		set_cpu_cap(c, X86_FEATURE_LFENCE_RDTSC);
	}

	/*
	 * Hygon processors have APIC timer running in deep C states.
	 */
	set_cpu_cap(c, X86_FEATURE_ARAT);

	/* Hygon CPUs don't reset SS attributes on SYSRET, Xen does. */
	if (!cpu_has(c, X86_FEATURE_XENPV))
		set_cpu_bug(c, X86_BUG_SYSRET_SS_ATTRS);
}