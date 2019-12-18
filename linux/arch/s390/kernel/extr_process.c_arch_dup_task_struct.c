#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fprs; int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {TYPE_1__ fpu; } ;
struct task_struct {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_task_struct_size ; 
 int /*<<< orphan*/  memcpy (struct task_struct*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_fpu_regs () ; 

int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
{
	/*
	 * Save the floating-point or vector register state of the current
	 * task and set the CIF_FPU flag to lazy restore the FPU register
	 * state when returning to user space.
	 */
	save_fpu_regs();

	memcpy(dst, src, arch_task_struct_size);
	dst->thread.fpu.regs = dst->thread.fpu.fprs;
	return 0;
}