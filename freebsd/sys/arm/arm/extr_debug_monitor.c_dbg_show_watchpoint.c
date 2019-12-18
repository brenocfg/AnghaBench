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
typedef  int /*<<< orphan*/  db_addr_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int DBGWVR_ADDR_MASK ; 
 int /*<<< orphan*/  DBG_REG_BASE_WCR ; 
 int /*<<< orphan*/  DBG_REG_BASE_WVR ; 
 int DBG_WB_CTRL_ACCESS_MASK (int) ; 
 int DBG_WB_CTRL_E ; 
 int DBG_WB_CTRL_LEN_MASK (int) ; 
 int /*<<< orphan*/  DB_STGY_ANY ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_capable () ; 
 int dbg_watchpoint_num ; 
 int /*<<< orphan*/  dbg_watchtype_len (int) ; 
 char* dbg_watchtype_str (int) ; 
 int dbg_wb_read_reg (int /*<<< orphan*/ ,int) ; 

void
dbg_show_watchpoint(void)
{
	uint32_t wcr, len, type;
	uint32_t addr;
	boolean_t is_enabled;
	int i;

	if (!dbg_capable()) {
		db_printf("Architecture does not support HW "
		    "breakpoints/watchpoints\n");
		return;
	}

	db_printf("\nhardware watchpoints:\n");
	db_printf("  watch    status        type  len     address              symbol\n");
	db_printf("  -----  --------  ----------  ---  ----------  ------------------\n");
	for (i = 0; i < dbg_watchpoint_num; i++) {
		wcr = dbg_wb_read_reg(DBG_REG_BASE_WCR, i);
		if ((wcr & DBG_WB_CTRL_E) != 0)
			is_enabled = TRUE;
		else
			is_enabled = FALSE;

		type = DBG_WB_CTRL_ACCESS_MASK(wcr);
		len = DBG_WB_CTRL_LEN_MASK(wcr);
		addr = dbg_wb_read_reg(DBG_REG_BASE_WVR, i) & DBGWVR_ADDR_MASK;
		db_printf("  %-5d  %-8s  %10s  %3d  0x%08x  ", i,
		    is_enabled ? "enabled" : "disabled",
		    is_enabled ? dbg_watchtype_str(type) : "",
		    is_enabled ? dbg_watchtype_len(len) : 0,
		    addr);
		db_printsym((db_addr_t)addr, DB_STGY_ANY);
		db_printf("\n");
	}
}