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
struct cpuinfo_x86 {int x86_vendor; } ;

/* Variables and functions */
#define  X86_VENDOR_INTEL 128 
 int /*<<< orphan*/  mce_intel_feature_clear (struct cpuinfo_x86*) ; 

__attribute__((used)) static void __mcheck_cpu_clear_vendor(struct cpuinfo_x86 *c)
{
	switch (c->x86_vendor) {
	case X86_VENDOR_INTEL:
		mce_intel_feature_clear(c);
		break;
	default:
		break;
	}
}