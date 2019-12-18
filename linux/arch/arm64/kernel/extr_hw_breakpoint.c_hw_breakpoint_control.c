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
typedef  int u32 ;
struct perf_event {int dummy; } ;
struct debug_info {int /*<<< orphan*/  wps_disabled; int /*<<< orphan*/  bps_disabled; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  privilege; } ;
struct arch_hw_breakpoint {int address; TYPE_2__ ctrl; } ;
typedef  enum hw_breakpoint_ops { ____Placeholder_hw_breakpoint_ops } hw_breakpoint_ops ;
typedef  enum dbg_active_el { ____Placeholder_dbg_active_el } dbg_active_el ;
struct TYPE_4__ {struct debug_info debug; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int AARCH64_DBG_REG_BCR ; 
 int AARCH64_DBG_REG_BVR ; 
 int AARCH64_DBG_REG_WCR ; 
 int AARCH64_DBG_REG_WVR ; 
 scalar_t__ ARM_BREAKPOINT_EXECUTE ; 
#define  HW_BREAKPOINT_INSTALL 130 
#define  HW_BREAKPOINT_RESTORE 129 
#define  HW_BREAKPOINT_UNINSTALL 128 
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  bp_on_reg ; 
 int core_num_brps ; 
 int core_num_wrps ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 TYPE_3__* current ; 
 int debug_exception_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_debug_monitors (int) ; 
 int /*<<< orphan*/  enable_debug_monitors (int) ; 
 int encode_ctrl_reg (TYPE_2__) ; 
 int hw_breakpoint_slot_setup (struct perf_event**,int,struct perf_event*,int) ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_on_reg ; 
 int /*<<< orphan*/  write_wb_reg (int,int,int) ; 

__attribute__((used)) static int hw_breakpoint_control(struct perf_event *bp,
				 enum hw_breakpoint_ops ops)
{
	struct arch_hw_breakpoint *info = counter_arch_bp(bp);
	struct perf_event **slots;
	struct debug_info *debug_info = &current->thread.debug;
	int i, max_slots, ctrl_reg, val_reg, reg_enable;
	enum dbg_active_el dbg_el = debug_exception_level(info->ctrl.privilege);
	u32 ctrl;

	if (info->ctrl.type == ARM_BREAKPOINT_EXECUTE) {
		/* Breakpoint */
		ctrl_reg = AARCH64_DBG_REG_BCR;
		val_reg = AARCH64_DBG_REG_BVR;
		slots = this_cpu_ptr(bp_on_reg);
		max_slots = core_num_brps;
		reg_enable = !debug_info->bps_disabled;
	} else {
		/* Watchpoint */
		ctrl_reg = AARCH64_DBG_REG_WCR;
		val_reg = AARCH64_DBG_REG_WVR;
		slots = this_cpu_ptr(wp_on_reg);
		max_slots = core_num_wrps;
		reg_enable = !debug_info->wps_disabled;
	}

	i = hw_breakpoint_slot_setup(slots, max_slots, bp, ops);

	if (WARN_ONCE(i < 0, "Can't find any breakpoint slot"))
		return i;

	switch (ops) {
	case HW_BREAKPOINT_INSTALL:
		/*
		 * Ensure debug monitors are enabled at the correct exception
		 * level.
		 */
		enable_debug_monitors(dbg_el);
		/* Fall through */
	case HW_BREAKPOINT_RESTORE:
		/* Setup the address register. */
		write_wb_reg(val_reg, i, info->address);

		/* Setup the control register. */
		ctrl = encode_ctrl_reg(info->ctrl);
		write_wb_reg(ctrl_reg, i,
			     reg_enable ? ctrl | 0x1 : ctrl & ~0x1);
		break;
	case HW_BREAKPOINT_UNINSTALL:
		/* Reset the control register. */
		write_wb_reg(ctrl_reg, i, 0);

		/*
		 * Release the debug monitors for the correct exception
		 * level.
		 */
		disable_debug_monitors(dbg_el);
		break;
	}

	return 0;
}