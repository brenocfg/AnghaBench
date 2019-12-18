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
struct thread {TYPE_1__* td_pcb; } ;
struct debug_monitor_state {scalar_t__ dbg_enable_count; int* dbg_bcr; int /*<<< orphan*/  dbg_flags; int /*<<< orphan*/ * dbg_bvr; } ;
struct dbreg {TYPE_2__* db_regs; } ;
struct TYPE_4__ {int dbr_ctrl; int /*<<< orphan*/  dbr_addr; } ;
struct TYPE_3__ {struct debug_monitor_state pcb_dbg_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMON_ENABLED ; 
 int DBG_BRP_MAX ; 

int
set_dbregs(struct thread *td, struct dbreg *regs)
{
	struct debug_monitor_state *monitor;
	int count;
	int i;

	monitor = &td->td_pcb->pcb_dbg_regs;
	count = 0;
	monitor->dbg_enable_count = 0;
	for (i = 0; i < DBG_BRP_MAX; i++) {
		/* TODO: Check these values */
		monitor->dbg_bvr[i] = regs->db_regs[i].dbr_addr;
		monitor->dbg_bcr[i] = regs->db_regs[i].dbr_ctrl;
		if ((monitor->dbg_bcr[i] & 1) != 0)
			monitor->dbg_enable_count++;
	}
	if (monitor->dbg_enable_count > 0)
		monitor->dbg_flags |= DBGMON_ENABLED;

	return (0);
}