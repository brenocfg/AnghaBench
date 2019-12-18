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
struct arch_hw_breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_brk ; 
 scalar_t__ dawr_enabled () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct arch_hw_breakpoint*,int) ; 
 int /*<<< orphan*/  set_dabr (struct arch_hw_breakpoint*) ; 
 int /*<<< orphan*/  set_dawr (struct arch_hw_breakpoint*) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

void __set_breakpoint(struct arch_hw_breakpoint *brk)
{
	memcpy(this_cpu_ptr(&current_brk), brk, sizeof(*brk));

	if (dawr_enabled())
		// Power8 or later
		set_dawr(brk);
	else if (!cpu_has_feature(CPU_FTR_ARCH_207S))
		// Power7 or earlier
		set_dabr(brk);
	else
		// Shouldn't happen due to higher level checks
		WARN_ON_ONCE(1);
}