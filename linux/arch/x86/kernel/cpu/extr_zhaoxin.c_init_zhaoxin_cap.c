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
struct cpuinfo_x86 {int x86; void** x86_capability; } ;

/* Variables and functions */
 int ACE_ENABLED ; 
 int ACE_FCR ; 
 int ACE_PRESENT ; 
 size_t CPUID_C000_0001_EDX ; 
 int /*<<< orphan*/  MSR_ZHAOXIN_FCR57 ; 
 int RNG_ENABLE ; 
 int RNG_ENABLED ; 
 int RNG_PRESENT ; 
 int /*<<< orphan*/  X86_FEATURE_REP_GOOD ; 
 int /*<<< orphan*/  cpu_detect_cache_sizes (struct cpuinfo_x86*) ; 
 int cpuid_eax (int) ; 
 void* cpuid_edx (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void init_zhaoxin_cap(struct cpuinfo_x86 *c)
{
	u32  lo, hi;

	/* Test for Extended Feature Flags presence */
	if (cpuid_eax(0xC0000000) >= 0xC0000001) {
		u32 tmp = cpuid_edx(0xC0000001);

		/* Enable ACE unit, if present and disabled */
		if ((tmp & (ACE_PRESENT | ACE_ENABLED)) == ACE_PRESENT) {
			rdmsr(MSR_ZHAOXIN_FCR57, lo, hi);
			/* Enable ACE unit */
			lo |= ACE_FCR;
			wrmsr(MSR_ZHAOXIN_FCR57, lo, hi);
			pr_info("CPU: Enabled ACE h/w crypto\n");
		}

		/* Enable RNG unit, if present and disabled */
		if ((tmp & (RNG_PRESENT | RNG_ENABLED)) == RNG_PRESENT) {
			rdmsr(MSR_ZHAOXIN_FCR57, lo, hi);
			/* Enable RNG unit */
			lo |= RNG_ENABLE;
			wrmsr(MSR_ZHAOXIN_FCR57, lo, hi);
			pr_info("CPU: Enabled h/w RNG\n");
		}

		/*
		 * Store Extended Feature Flags as word 5 of the CPU
		 * capability bit array
		 */
		c->x86_capability[CPUID_C000_0001_EDX] = cpuid_edx(0xC0000001);
	}

	if (c->x86 >= 0x6)
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);

	cpu_detect_cache_sizes(c);
}