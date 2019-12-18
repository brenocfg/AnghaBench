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
struct cpuinfo_x86 {int x86; int x86_vendor; } ;

/* Variables and functions */
#define  X86_VENDOR_CENTAUR 129 
#define  X86_VENDOR_INTEL 128 
 int /*<<< orphan*/  intel_p5_mcheck_init (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  winchip_mcheck_init (struct cpuinfo_x86*) ; 

__attribute__((used)) static int __mcheck_cpu_ancient_init(struct cpuinfo_x86 *c)
{
	if (c->x86 != 5)
		return 0;

	switch (c->x86_vendor) {
	case X86_VENDOR_INTEL:
		intel_p5_mcheck_init(c);
		return 1;
		break;
	case X86_VENDOR_CENTAUR:
		winchip_mcheck_init(c);
		return 1;
		break;
	default:
		return 0;
	}

	return 0;
}