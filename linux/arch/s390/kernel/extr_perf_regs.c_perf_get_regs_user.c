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
struct pt_regs {int dummy; } ;
struct perf_regs {int /*<<< orphan*/  abi; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  perf_reg_abi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_fpu_regs () ; 
 int /*<<< orphan*/  task_pt_regs (int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (int /*<<< orphan*/ ) ; 

void perf_get_regs_user(struct perf_regs *regs_user,
			struct pt_regs *regs,
			struct pt_regs *regs_user_copy)
{
	/*
	 * Use the regs from the first interruption and let
	 * perf_sample_regs_intr() handle interrupts (regs == get_irq_regs()).
	 *
	 * Also save FPU registers for user-space tasks only.
	 */
	regs_user->regs = task_pt_regs(current);
	if (user_mode(regs_user->regs))
		save_fpu_regs();
	regs_user->abi = perf_reg_abi(current);
}