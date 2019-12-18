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
struct pt_regs {int int_code; scalar_t__ int_parm; int /*<<< orphan*/ * gprs; } ;

/* Variables and functions */
 scalar_t__ CPU_MF_INT_SF_PRA ; 
 unsigned long PERF_RECORD_MISC_KERNEL ; 
 unsigned long PERF_RECORD_MISC_USER ; 
 scalar_t__ is_in_guest (struct pt_regs*) ; 
 unsigned long perf_misc_flags_sf (struct pt_regs*) ; 
 unsigned long perf_misc_guest_flags (struct pt_regs*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

unsigned long perf_misc_flags(struct pt_regs *regs)
{
	/* Check if the cpum_sf PMU has created the pt_regs structure.
	 * In this case, perf misc flags can be easily extracted.  Otherwise,
	 * do regular checks on the pt_regs content.
	 */
	if (regs->int_code == 0x1407 && regs->int_parm == CPU_MF_INT_SF_PRA)
		if (!regs->gprs[15])
			return perf_misc_flags_sf(regs);

	if (is_in_guest(regs))
		return perf_misc_guest_flags(regs);

	return user_mode(regs) ? PERF_RECORD_MISC_USER
			       : PERF_RECORD_MISC_KERNEL;
}