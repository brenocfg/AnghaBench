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
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int DBGWVR_ADDR_MASK ; 
 int /*<<< orphan*/  DBG_BKPT_BNT_SLOT ; 
 int /*<<< orphan*/  DBG_BKPT_BT_SLOT ; 
 int /*<<< orphan*/  DBG_REG_BASE_WCR ; 
 int /*<<< orphan*/  DBG_REG_BASE_WVR ; 
 int DBG_WB_CTRL_E ; 
 int /*<<< orphan*/  dbg_capable () ; 
 int /*<<< orphan*/  dbg_remove_breakpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ dbg_watchpoint_num ; 
 int dbg_wb_read_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dbg_wb_write_reg (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
kdb_cpu_clear_singlestep(void)
{
	uint32_t wvr, wcr;
	u_int i;

	if (!dbg_capable())
		return;

	dbg_remove_breakpoint(DBG_BKPT_BT_SLOT);
	dbg_remove_breakpoint(DBG_BKPT_BNT_SLOT);

	/* Restore all watchpoints */
	for (i = 0; i < dbg_watchpoint_num; i++) {
		wcr = dbg_wb_read_reg(DBG_REG_BASE_WCR, i);
		wvr = dbg_wb_read_reg(DBG_REG_BASE_WVR, i);
		/* Watchpoint considered not empty if address value is not 0 */
		if ((wvr & DBGWVR_ADDR_MASK) != 0) {
			dbg_wb_write_reg(DBG_REG_BASE_WCR, i,
			    (wcr | DBG_WB_CTRL_E));
		}
	}
}