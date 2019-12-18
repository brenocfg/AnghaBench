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
struct cpuinfo_x86 {int x86; int x86_model; int x86_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_CENTAUR_MCR ; 
 int /*<<< orphan*/  X86_FEATURE_CONSTANT_TSC ; 
 int /*<<< orphan*/  X86_FEATURE_NONSTOP_TSC ; 
 int /*<<< orphan*/  X86_FEATURE_SYSENTER32 ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void early_init_centaur(struct cpuinfo_x86 *c)
{
	switch (c->x86) {
#ifdef CONFIG_X86_32
	case 5:
		/* Emulate MTRRs using Centaur's MCR. */
		set_cpu_cap(c, X86_FEATURE_CENTAUR_MCR);
		break;
#endif
	case 6:
		if (c->x86_model >= 0xf)
			set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		break;
	}
#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_SYSENTER32);
#endif
	if (c->x86_power & (1 << 8)) {
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC);
	}
}