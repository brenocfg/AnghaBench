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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_high ; 
 int /*<<< orphan*/  cpu_vendor_id ; 
 int /*<<< orphan*/  do_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_cpu_vendor_id () ; 
 scalar_t__ fix_cpuid () ; 

void
identify_cpu_fixup_bsp(void)
{
	u_int regs[4];

	cpu_vendor_id = find_cpu_vendor_id();

	if (fix_cpuid()) {
		do_cpuid(0, regs);
		cpu_high = regs[0];
	}
}