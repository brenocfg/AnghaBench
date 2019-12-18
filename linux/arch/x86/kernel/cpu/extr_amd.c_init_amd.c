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
struct cpuinfo_x86 {int x86; int /*<<< orphan*/  apicid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_F10H_DECFG ; 
 int /*<<< orphan*/  MSR_F10H_DECFG_LFENCE_SERIALIZE_BIT ; 
 int /*<<< orphan*/  X86_BUG_FXSAVE_LEAK ; 
 int /*<<< orphan*/  X86_BUG_SYSRET_SS_ATTRS ; 
 int /*<<< orphan*/  X86_FEATURE_3DNOW ; 
 int /*<<< orphan*/  X86_FEATURE_3DNOWPREFETCH ; 
 int /*<<< orphan*/  X86_FEATURE_ARAT ; 
 int /*<<< orphan*/  X86_FEATURE_LFENCE_RDTSC ; 
 int /*<<< orphan*/  X86_FEATURE_LM ; 
 int X86_FEATURE_MCE ; 
 int /*<<< orphan*/  X86_FEATURE_REP_GOOD ; 
 int /*<<< orphan*/  X86_FEATURE_XENPV ; 
 int /*<<< orphan*/  X86_FEATURE_XMM2 ; 
 int /*<<< orphan*/  X86_FEATURE_XSAVEERPTR ; 
 int /*<<< orphan*/  amd_detect_cmp (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  amd_get_topology (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  clear_cpu_cap (struct cpuinfo_x86*,int) ; 
 int /*<<< orphan*/  cpu_detect_cache_sizes (struct cpuinfo_x86*) ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  early_init_amd (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  hard_smp_processor_id () ; 
 int /*<<< orphan*/  init_amd_bd (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_cacheinfo (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_gh (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_jg (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_k5 (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_k6 (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_k7 (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_k8 (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_ln (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_amd_zn (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  msr_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_bug (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srat_detect_node (struct cpuinfo_x86*) ; 

__attribute__((used)) static void init_amd(struct cpuinfo_x86 *c)
{
	early_init_amd(c);

	/*
	 * Bit 31 in normal CPUID used for nonstandard 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	clear_cpu_cap(c, 0*32+31);

	if (c->x86 >= 0x10)
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);

	/* get apicid instead of initial apic id from cpuid */
	c->apicid = hard_smp_processor_id();

	/* K6s reports MCEs but don't actually have all the MSRs */
	if (c->x86 < 6)
		clear_cpu_cap(c, X86_FEATURE_MCE);

	switch (c->x86) {
	case 4:    init_amd_k5(c); break;
	case 5:    init_amd_k6(c); break;
	case 6:	   init_amd_k7(c); break;
	case 0xf:  init_amd_k8(c); break;
	case 0x10: init_amd_gh(c); break;
	case 0x12: init_amd_ln(c); break;
	case 0x15: init_amd_bd(c); break;
	case 0x16: init_amd_jg(c); break;
	case 0x17: init_amd_zn(c); break;
	}

	/*
	 * Enable workaround for FXSAVE leak on CPUs
	 * without a XSaveErPtr feature
	 */
	if ((c->x86 >= 6) && (!cpu_has(c, X86_FEATURE_XSAVEERPTR)))
		set_cpu_bug(c, X86_BUG_FXSAVE_LEAK);

	cpu_detect_cache_sizes(c);

	amd_detect_cmp(c);
	amd_get_topology(c);
	srat_detect_node(c);

	init_amd_cacheinfo(c);

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
	 * Family 0x12 and above processors have APIC timer
	 * running in deep C states.
	 */
	if (c->x86 > 0x11)
		set_cpu_cap(c, X86_FEATURE_ARAT);

	/* 3DNow or LM implies PREFETCHW */
	if (!cpu_has(c, X86_FEATURE_3DNOWPREFETCH))
		if (cpu_has(c, X86_FEATURE_3DNOW) || cpu_has(c, X86_FEATURE_LM))
			set_cpu_cap(c, X86_FEATURE_3DNOWPREFETCH);

	/* AMD CPUs don't reset SS attributes on SYSRET, Xen does. */
	if (!cpu_has(c, X86_FEATURE_XENPV))
		set_cpu_bug(c, X86_BUG_SYSRET_SS_ATTRS);
}