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
typedef  int uint8_t ;
struct thread {TYPE_1__* td_pcb; } ;
struct debug_monitor_state {int dbg_flags; int /*<<< orphan*/ * dbg_bcr; int /*<<< orphan*/ * dbg_bvr; } ;
struct dbreg {int db_info; TYPE_2__* db_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dbr_ctrl; int /*<<< orphan*/  dbr_addr; } ;
struct TYPE_3__ {struct debug_monitor_state pcb_dbg_regs; } ;

/* Variables and functions */
 int DBGMON_ENABLED ; 
 int /*<<< orphan*/  ID_AA64DFR0_BRPs_SHIFT ; 
 int /*<<< orphan*/  ID_AA64DFR0_DebugVer_SHIFT ; 
 int /*<<< orphan*/  ID_AA64DFR0_EL1 ; 
 int /*<<< orphan*/  extract_user_id_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (struct dbreg*,int /*<<< orphan*/ ,int) ; 

int
fill_dbregs(struct thread *td, struct dbreg *regs)
{
	struct debug_monitor_state *monitor;
	int count, i;
	uint8_t debug_ver, nbkpts;

	memset(regs, 0, sizeof(*regs));

	extract_user_id_field(ID_AA64DFR0_EL1, ID_AA64DFR0_DebugVer_SHIFT,
	    &debug_ver);
	extract_user_id_field(ID_AA64DFR0_EL1, ID_AA64DFR0_BRPs_SHIFT,
	    &nbkpts);

	/*
	 * The BRPs field contains the number of breakpoints - 1. Armv8-A
	 * allows the hardware to provide 2-16 breakpoints so this won't
	 * overflow an 8 bit value.
	 */
	count = nbkpts + 1;

	regs->db_info = debug_ver;
	regs->db_info <<= 8;
	regs->db_info |= count;

	monitor = &td->td_pcb->pcb_dbg_regs;
	if ((monitor->dbg_flags & DBGMON_ENABLED) != 0) {
		for (i = 0; i < count; i++) {
			regs->db_regs[i].dbr_addr = monitor->dbg_bvr[i];
			regs->db_regs[i].dbr_ctrl = monitor->dbg_bcr[i];
		}
	}

	return (0);
}