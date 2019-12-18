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
typedef  int u32 ;
struct perf_event {int dummy; } ;
typedef  enum dbg_active_el { ____Placeholder_dbg_active_el } dbg_active_el ;
struct TYPE_3__ {int privilege; } ;
struct TYPE_4__ {TYPE_1__ ctrl; } ;

/* Variables and functions */
#define  AARCH64_DBG_REG_BCR 129 
#define  AARCH64_DBG_REG_WCR 128 
 int /*<<< orphan*/  bp_on_reg ; 
 int core_num_brps ; 
 int core_num_wrps ; 
 TYPE_2__* counter_arch_bp (struct perf_event*) ; 
 int debug_exception_level (int) ; 
 int read_wb_reg (int,int) ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_on_reg ; 
 int /*<<< orphan*/  write_wb_reg (int,int,int) ; 

__attribute__((used)) static void toggle_bp_registers(int reg, enum dbg_active_el el, int enable)
{
	int i, max_slots, privilege;
	u32 ctrl;
	struct perf_event **slots;

	switch (reg) {
	case AARCH64_DBG_REG_BCR:
		slots = this_cpu_ptr(bp_on_reg);
		max_slots = core_num_brps;
		break;
	case AARCH64_DBG_REG_WCR:
		slots = this_cpu_ptr(wp_on_reg);
		max_slots = core_num_wrps;
		break;
	default:
		return;
	}

	for (i = 0; i < max_slots; ++i) {
		if (!slots[i])
			continue;

		privilege = counter_arch_bp(slots[i])->ctrl.privilege;
		if (debug_exception_level(privilege) != el)
			continue;

		ctrl = read_wb_reg(reg, i);
		if (enable)
			ctrl |= 0x1;
		else
			ctrl &= ~0x1;
		write_wb_reg(reg, i, ctrl);
	}
}