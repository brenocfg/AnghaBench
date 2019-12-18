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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  int u_int ;
struct debug_monitor_state {scalar_t__* dbg_wcr; scalar_t__* dbg_wvr; scalar_t__* dbg_bcr; scalar_t__* dbg_bvr; } ;
typedef  enum dbg_t { ____Placeholder_dbg_t } dbg_t ;

/* Variables and functions */
#define  DBG_TYPE_BREAKPOINT 129 
#define  DBG_TYPE_WATCHPOINT 128 
 scalar_t__ DBG_WB_CTRL_E ; 
 int dbg_breakpoint_num ; 
 int dbg_watchpoint_num ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
dbg_find_slot(struct debug_monitor_state *monitor, enum dbg_t type,
    vm_offset_t addr)
{
	uint64_t *reg_addr, *reg_ctrl;
	u_int max, i;

	switch(type) {
	case DBG_TYPE_BREAKPOINT:
		max = dbg_breakpoint_num;
		reg_addr = monitor->dbg_bvr;
		reg_ctrl = monitor->dbg_bcr;
		break;
	case DBG_TYPE_WATCHPOINT:
		max = dbg_watchpoint_num;
		reg_addr = monitor->dbg_wvr;
		reg_ctrl = monitor->dbg_wcr;
		break;
	default:
		printf("Unsupported debug type\n");
		return (i);
	}

	for (i = 0; i < max; i++) {
		if (reg_addr[i] == addr &&
		    (reg_ctrl[i] & DBG_WB_CTRL_E) != 0)
			return (i);
	}

	return (-1);
}