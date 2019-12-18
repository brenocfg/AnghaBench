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
typedef  int /*<<< orphan*/  pc ;
typedef  int /*<<< orphan*/  db_expr_t ;
typedef  int /*<<< orphan*/  db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BKPT_BNT_SLOT ; 
 int /*<<< orphan*/  DBG_BKPT_BT_SLOT ; 
 int /*<<< orphan*/  DBG_REG_BASE_WCR ; 
 int DBG_WB_CTRL_E ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INSN_SIZE ; 
 int /*<<< orphan*/  PC_REGS () ; 
 int /*<<< orphan*/  branch_taken (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_get_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_capable () ; 
 int /*<<< orphan*/  dbg_setup_breakpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dbg_watchpoint_num ; 
 int dbg_wb_read_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dbg_wb_write_reg (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ inst_branch (int /*<<< orphan*/ ) ; 
 scalar_t__ inst_call (int /*<<< orphan*/ ) ; 
 scalar_t__ inst_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_instr_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kdb_cpu_set_singlestep(void)
{
	db_expr_t inst;
	db_addr_t pc, brpc;
	uint32_t wcr;
	u_int i;

	if (!dbg_capable())
		return;

	/*
	 * Disable watchpoints, e.g. stepping over watched instruction will
	 * trigger break exception instead of single-step exception and locks
	 * CPU on that instruction for ever.
	 */
	for (i = 0; i < dbg_watchpoint_num; i++) {
		wcr = dbg_wb_read_reg(DBG_REG_BASE_WCR, i);
		if ((wcr & DBG_WB_CTRL_E) != 0) {
			dbg_wb_write_reg(DBG_REG_BASE_WCR, i,
			    (wcr & ~DBG_WB_CTRL_E));
		}
	}

	pc = PC_REGS();

	inst = db_get_value(pc, sizeof(pc), FALSE);
	if (inst_branch(inst) || inst_call(inst) || inst_return(inst)) {
		brpc = branch_taken(inst, pc);
		dbg_setup_breakpoint(brpc, INSN_SIZE, DBG_BKPT_BT_SLOT);
	}
	pc = next_instr_address(pc, 0);
	dbg_setup_breakpoint(pc, INSN_SIZE, DBG_BKPT_BNT_SLOT);
}