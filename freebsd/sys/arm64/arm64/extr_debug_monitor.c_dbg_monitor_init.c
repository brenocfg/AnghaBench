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
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_REG_BASE_BCR ; 
 int /*<<< orphan*/  DBG_REG_BASE_BVR ; 
 int /*<<< orphan*/  DBG_REG_BASE_WCR ; 
 int /*<<< orphan*/  DBG_REG_BASE_WVR ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cpuid ; 
 int dbg_breakpoint_num ; 
 int /*<<< orphan*/  dbg_enable () ; 
 int dbg_watchpoint_num ; 
 int /*<<< orphan*/  dbg_wb_write_reg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_aa64dfr0_el1 ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void
dbg_monitor_init(void)
{
	u_int i;

	/* Find out many breakpoints and watchpoints we can use */
	dbg_watchpoint_num = ((READ_SPECIALREG(id_aa64dfr0_el1) >> 20) & 0xf) + 1;
	dbg_breakpoint_num = ((READ_SPECIALREG(id_aa64dfr0_el1) >> 12) & 0xf) + 1;

	if (bootverbose && PCPU_GET(cpuid) == 0) {
		printf("%d watchpoints and %d breakpoints supported\n",
		    dbg_watchpoint_num, dbg_breakpoint_num);
	}

	/*
	 * We have limited number of {watch,break}points, each consists of
	 * two registers:
	 * - wcr/bcr regsiter configurates corresponding {watch,break}point
	 *   behaviour
	 * - wvr/bvr register keeps address we are hunting for
	 *
	 * Reset all breakpoints and watchpoints.
	 */
	for (i = 0; i < dbg_watchpoint_num; i++) {
		dbg_wb_write_reg(DBG_REG_BASE_WCR, i, 0);
		dbg_wb_write_reg(DBG_REG_BASE_WVR, i, 0);
	}

	for (i = 0; i < dbg_breakpoint_num; i++) {
		dbg_wb_write_reg(DBG_REG_BASE_BCR, i, 0);
		dbg_wb_write_reg(DBG_REG_BASE_BVR, i, 0);
	}

	dbg_enable();
}