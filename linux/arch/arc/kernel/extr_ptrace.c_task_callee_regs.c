#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ callee_reg; } ;
struct task_struct {TYPE_1__ thread; } ;
struct callee_regs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct callee_regs *task_callee_regs(struct task_struct *tsk)
{
	struct callee_regs *tmp = (struct callee_regs *)tsk->thread.callee_reg;
	return tmp;
}