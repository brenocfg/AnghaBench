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
struct TYPE_2__ {scalar_t__ fault_code; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 scalar_t__ UPROBE_INV_FAULT_CODE ; 

bool arch_uprobe_xol_was_trapped(struct task_struct *t)
{
	/*
	 * Between arch_uprobe_pre_xol and arch_uprobe_post_xol, if an xol
	 * insn itself is trapped, then detect the case with the help of
	 * invalid fault code which is being set in arch_uprobe_pre_xol
	 */
	if (t->thread.fault_code != UPROBE_INV_FAULT_CODE)
		return true;

	return false;
}