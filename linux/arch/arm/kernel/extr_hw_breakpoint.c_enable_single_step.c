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
typedef  int /*<<< orphan*/  u32 ;
struct perf_event {int dummy; } ;
struct TYPE_4__ {int mismatch; int enabled; int /*<<< orphan*/  privilege; int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  privilege; } ;
struct arch_hw_breakpoint {int /*<<< orphan*/  trigger; TYPE_2__ step_ctrl; TYPE_1__ ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_BREAKPOINT_EXECUTE ; 
 int /*<<< orphan*/  ARM_BREAKPOINT_LEN_4 ; 
 int /*<<< orphan*/  arch_install_hw_breakpoint (struct perf_event*) ; 
 int /*<<< orphan*/  arch_uninstall_hw_breakpoint (struct perf_event*) ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 

__attribute__((used)) static void enable_single_step(struct perf_event *bp, u32 addr)
{
	struct arch_hw_breakpoint *info = counter_arch_bp(bp);

	arch_uninstall_hw_breakpoint(bp);
	info->step_ctrl.mismatch  = 1;
	info->step_ctrl.len	  = ARM_BREAKPOINT_LEN_4;
	info->step_ctrl.type	  = ARM_BREAKPOINT_EXECUTE;
	info->step_ctrl.privilege = info->ctrl.privilege;
	info->step_ctrl.enabled	  = 1;
	info->trigger		  = addr;
	arch_install_hw_breakpoint(bp);
}