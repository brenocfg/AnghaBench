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
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FSL_EMB_PERF_EVENT ; 
 int /*<<< orphan*/  CONFIG_PPC32 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PERF_REG_POWERPC_MAX ; 
 int PERF_REG_POWERPC_MMCRA ; 
 int PERF_REG_POWERPC_SIER ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  is_sier_available () ; 
 int /*<<< orphan*/ * pt_regs_offset ; 
 int /*<<< orphan*/  regs_get_register (struct pt_regs*,int /*<<< orphan*/ ) ; 

u64 perf_reg_value(struct pt_regs *regs, int idx)
{
	if (WARN_ON_ONCE(idx >= PERF_REG_POWERPC_MAX))
		return 0;

	if (idx == PERF_REG_POWERPC_SIER &&
	   (IS_ENABLED(CONFIG_FSL_EMB_PERF_EVENT) ||
	    IS_ENABLED(CONFIG_PPC32) ||
	    !is_sier_available()))
		return 0;

	if (idx == PERF_REG_POWERPC_MMCRA &&
	   (IS_ENABLED(CONFIG_FSL_EMB_PERF_EVENT) ||
	    IS_ENABLED(CONFIG_PPC32)))
		return 0;

	return regs_get_register(regs, pt_regs_offset[idx]);
}