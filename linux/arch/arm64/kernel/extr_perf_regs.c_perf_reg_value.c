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
typedef  scalar_t__ u32 ;
struct pt_regs {int /*<<< orphan*/ * regs; int /*<<< orphan*/  pc; int /*<<< orphan*/  sp; int /*<<< orphan*/  compat_lr; int /*<<< orphan*/  compat_sp; } ;

/* Variables and functions */
 scalar_t__ PERF_REG_ARM64_LR ; 
 scalar_t__ PERF_REG_ARM64_MAX ; 
 scalar_t__ PERF_REG_ARM64_PC ; 
 scalar_t__ PERF_REG_ARM64_SP ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ compat_user_mode (struct pt_regs*) ; 

u64 perf_reg_value(struct pt_regs *regs, int idx)
{
	if (WARN_ON_ONCE((u32)idx >= PERF_REG_ARM64_MAX))
		return 0;

	/*
	 * Compat (i.e. 32 bit) mode:
	 * - PC has been set in the pt_regs struct in kernel_entry,
	 * - Handle SP and LR here.
	 */
	if (compat_user_mode(regs)) {
		if ((u32)idx == PERF_REG_ARM64_SP)
			return regs->compat_sp;
		if ((u32)idx == PERF_REG_ARM64_LR)
			return regs->compat_lr;
	}

	if ((u32)idx == PERF_REG_ARM64_SP)
		return regs->sp;

	if ((u32)idx == PERF_REG_ARM64_PC)
		return regs->pc;

	return regs->regs[idx];
}