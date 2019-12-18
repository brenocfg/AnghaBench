#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  db_expr_t ;
typedef  TYPE_1__* db_breakpoint_t ;
typedef  void* db_addr_t ;
struct TYPE_3__ {scalar_t__ count; scalar_t__ init_count; } ;
typedef  void* FIXUP_PC_AFTER_BREAK ;

/* Variables and functions */
 int /*<<< orphan*/  BKPT_SKIP ; 
 int IS_BREAKPOINT_TRAP (int,int) ; 
 scalar_t__ IS_SSTEP_TRAP (int,int) ; 
 int IS_WATCHPOINT_TRAP (int,int) ; 
 void* PC_REGS () ; 
 scalar_t__ STEP_CALLT ; 
 scalar_t__ STEP_CONTINUE ; 
 scalar_t__ STEP_COUNT ; 
 scalar_t__ STEP_INVISIBLE ; 
 scalar_t__ STEP_ONCE ; 
 scalar_t__ STEP_RETURN ; 
 scalar_t__ db_call_depth ; 
 int /*<<< orphan*/  db_clear_breakpoints () ; 
 int /*<<< orphan*/  db_clear_single_step () ; 
 int /*<<< orphan*/  db_clear_watchpoints () ; 
 TYPE_1__* db_find_breakpoint_here (void*) ; 
 int /*<<< orphan*/  db_get_value (void*,int,int) ; 
 int /*<<< orphan*/  db_inst_count ; 
 scalar_t__ db_loop_count ; 
 scalar_t__ db_pc_is_singlestep (void*) ; 
 int /*<<< orphan*/  db_print_loc_and_inst (void*) ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 scalar_t__ db_run_mode ; 
 scalar_t__ db_sstep_print ; 
 scalar_t__ inst_call (int /*<<< orphan*/ ) ; 
 scalar_t__ inst_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inst_trap_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

bool
db_stop_at_pc(int type, int code, bool *is_breakpoint, bool *is_watchpoint)
{
	db_addr_t	pc;
	db_breakpoint_t bkpt;

	*is_breakpoint = IS_BREAKPOINT_TRAP(type, code);
	*is_watchpoint = IS_WATCHPOINT_TRAP(type, code);
	pc = PC_REGS();
	if (db_pc_is_singlestep(pc))
		*is_breakpoint = false;

	db_clear_single_step();
	db_clear_breakpoints();
	db_clear_watchpoints();

#ifdef	FIXUP_PC_AFTER_BREAK
	if (*is_breakpoint) {
	    /*
	     * Breakpoint trap.  Fix up the PC if the
	     * machine requires it.
	     */
	    FIXUP_PC_AFTER_BREAK
	    pc = PC_REGS();
	}
#endif

	/*
	 * Now check for a breakpoint at this address.
	 */
	bkpt = db_find_breakpoint_here(pc);
	if (bkpt) {
	    if (--bkpt->count == 0) {
		bkpt->count = bkpt->init_count;
		*is_breakpoint = true;
		return (true);	/* stop here */
	    }
	    return (false);	/* continue the countdown */
	} else if (*is_breakpoint) {
#ifdef BKPT_SKIP
		BKPT_SKIP;
#endif
	}

	*is_breakpoint = false;	/* might be a breakpoint, but not ours */

	/*
	 * If not stepping, then silently ignore single-step traps
	 * (except for clearing the single-step-flag above).
	 *
	 * If stepping, then abort if the trap type is unexpected.
	 * Breakpoints owned by us are expected and were handled above.
	 * Single-steps are expected and are handled below.  All others
	 * are unexpected.
	 *
	 * Only do either of these if the MD layer claims to classify
	 * single-step traps unambiguously (by defining IS_SSTEP_TRAP).
	 * Otherwise, fall through to the bad historical behaviour
	 * given by turning unexpected traps into expected traps: if not
	 * stepping, then expect only breakpoints and stop, and if
	 * stepping, then expect only single-steps and step.
	 */
#ifdef IS_SSTEP_TRAP
	if (db_run_mode == STEP_CONTINUE && IS_SSTEP_TRAP(type, code))
	    return (false);
	if (db_run_mode != STEP_CONTINUE && !IS_SSTEP_TRAP(type, code)) {
	    printf("Stepping aborted\n");
	    return (true);
	}
#endif

	if (db_run_mode == STEP_INVISIBLE) {
	    db_run_mode = STEP_CONTINUE;
	    return (false);	/* continue */
	}
	if (db_run_mode == STEP_COUNT) {
	    return (false); /* continue */
	}
	if (db_run_mode == STEP_ONCE) {
	    if (--db_loop_count > 0) {
		if (db_sstep_print) {
		    db_printf("\t\t");
		    db_print_loc_and_inst(pc);
		}
		return (false);	/* continue */
	    }
	}
	if (db_run_mode == STEP_RETURN) {
	    /* continue until matching return */
	    db_expr_t ins;

	    ins = db_get_value(pc, sizeof(int), false);
	    if (!inst_trap_return(ins) &&
		(!inst_return(ins) || --db_call_depth != 0)) {
		if (db_sstep_print) {
		    if (inst_call(ins) || inst_return(ins)) {
			int i;

			db_printf("[after %6d]     ", db_inst_count);
			for (i = db_call_depth; --i > 0; )
			    db_printf("  ");
			db_print_loc_and_inst(pc);
		    }
		}
		if (inst_call(ins))
		    db_call_depth++;
		return (false);	/* continue */
	    }
	}
	if (db_run_mode == STEP_CALLT) {
	    /* continue until call or return */
	    db_expr_t ins;

	    ins = db_get_value(pc, sizeof(int), false);
	    if (!inst_call(ins) &&
		!inst_return(ins) &&
		!inst_trap_return(ins)) {
		return (false);	/* continue */
	    }
	}
	return (true);
}