#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct debug_info {scalar_t__ bps_disabled; scalar_t__ wps_disabled; } ;
struct TYPE_5__ {struct debug_info debug; } ;
struct task_struct {TYPE_2__ thread; } ;
struct TYPE_4__ {struct debug_info debug; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_DBG_REG_BCR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_WCR ; 
 int /*<<< orphan*/  DBG_ACTIVE_EL0 ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  toggle_bp_registers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hw_breakpoint_thread_switch(struct task_struct *next)
{
	/*
	 *           current        next
	 * disabled: 0              0     => The usual case, NOTIFY_DONE
	 *           0              1     => Disable the registers
	 *           1              0     => Enable the registers
	 *           1              1     => NOTIFY_DONE. per-task bps will
	 *                                   get taken care of by perf.
	 */

	struct debug_info *current_debug_info, *next_debug_info;

	current_debug_info = &current->thread.debug;
	next_debug_info = &next->thread.debug;

	/* Update breakpoints. */
	if (current_debug_info->bps_disabled != next_debug_info->bps_disabled)
		toggle_bp_registers(AARCH64_DBG_REG_BCR,
				    DBG_ACTIVE_EL0,
				    !next_debug_info->bps_disabled);

	/* Update watchpoints. */
	if (current_debug_info->wps_disabled != next_debug_info->wps_disabled)
		toggle_bp_registers(AARCH64_DBG_REG_WCR,
				    DBG_ACTIVE_EL0,
				    !next_debug_info->wps_disabled);
}