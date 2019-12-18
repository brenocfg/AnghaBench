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
struct cpuinfo_x86 {int x86_model; int x86; int x86_cache_alignment; int x86_clflush_size; void** x86_capability; } ;

/* Variables and functions */
 int ACE_ENABLED ; 
 int ACE_FCR ; 
 int ACE_PRESENT ; 
 size_t CPUID_C000_0001_EDX ; 
 int /*<<< orphan*/  MSR_VIA_FCR ; 
 int /*<<< orphan*/  MSR_VIA_RNG ; 
 int RNG_ENABLE ; 
 int RNG_ENABLED ; 
 int RNG_PRESENT ; 
 int /*<<< orphan*/  X86_FEATURE_3DNOW ; 
 int /*<<< orphan*/  X86_FEATURE_CX8 ; 
 int /*<<< orphan*/  X86_FEATURE_REP_GOOD ; 
 int /*<<< orphan*/  cpu_detect_cache_sizes (struct cpuinfo_x86*) ; 
 int cpuid_eax (int) ; 
 void* cpuid_edx (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void init_c3(struct cpuinfo_x86 *c)
{
	u32  lo, hi;

	/* Test for Centaur Extended Feature Flags presence */
	if (cpuid_eax(0xC0000000) >= 0xC0000001) {
		u32 tmp = cpuid_edx(0xC0000001);

		/* enable ACE unit, if present and disabled */
		if ((tmp & (ACE_PRESENT | ACE_ENABLED)) == ACE_PRESENT) {
			rdmsr(MSR_VIA_FCR, lo, hi);
			lo |= ACE_FCR;		/* enable ACE unit */
			wrmsr(MSR_VIA_FCR, lo, hi);
			pr_info("CPU: Enabled ACE h/w crypto\n");
		}

		/* enable RNG unit, if present and disabled */
		if ((tmp & (RNG_PRESENT | RNG_ENABLED)) == RNG_PRESENT) {
			rdmsr(MSR_VIA_RNG, lo, hi);
			lo |= RNG_ENABLE;	/* enable RNG unit */
			wrmsr(MSR_VIA_RNG, lo, hi);
			pr_info("CPU: Enabled h/w RNG\n");
		}

		/* store Centaur Extended Feature Flags as
		 * word 5 of the CPU capability bit array
		 */
		c->x86_capability[CPUID_C000_0001_EDX] = cpuid_edx(0xC0000001);
	}
#ifdef CONFIG_X86_32
	/* Cyrix III family needs CX8 & PGE explicitly enabled. */
	if (c->x86_model >= 6 && c->x86_model <= 13) {
		rdmsr(MSR_VIA_FCR, lo, hi);
		lo |= (1<<1 | 1<<7);
		wrmsr(MSR_VIA_FCR, lo, hi);
		set_cpu_cap(c, X86_FEATURE_CX8);
	}

	/* Before Nehemiah, the C3's had 3dNOW! */
	if (c->x86_model >= 6 && c->x86_model < 9)
		set_cpu_cap(c, X86_FEATURE_3DNOW);
#endif
	if (c->x86 == 0x6 && c->x86_model >= 0xf) {
		c->x86_cache_alignment = c->x86_clflush_size * 2;
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);
	}

	cpu_detect_cache_sizes(c);
}