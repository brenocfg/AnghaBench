#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_2__* td_pcb; } ;
struct TYPE_7__ {int dbg_flags; } ;
struct TYPE_5__ {int dbg_flags; } ;
struct TYPE_6__ {TYPE_1__ pcb_dbg_regs; } ;

/* Variables and functions */
 int DBGMON_ENABLED ; 
 int DBG_MDSCR_KDE ; 
 int DBG_MDSCR_MDE ; 
 int /*<<< orphan*/  DBG_REG_BASE_BCR ; 
 int /*<<< orphan*/  DBG_REG_BASE_BVR ; 
 int /*<<< orphan*/  DBG_REG_BASE_WCR ; 
 int /*<<< orphan*/  DBG_REG_BASE_WVR ; 
 int READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_SPECIALREG (int /*<<< orphan*/ ,int) ; 
 int dbg_breakpoint_num ; 
 int /*<<< orphan*/  dbg_register_sync (TYPE_3__*) ; 
 int dbg_watchpoint_num ; 
 int /*<<< orphan*/  dbg_wb_write_reg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 
 TYPE_3__ kernel_monitor ; 
 int /*<<< orphan*/  mdscr_el1 ; 

void
dbg_monitor_enter(struct thread *thread)
{
	int i;

	if ((kernel_monitor.dbg_flags & DBGMON_ENABLED) != 0) {
		/* Install the kernel version of the registers */
		dbg_register_sync(&kernel_monitor);
	} else if ((thread->td_pcb->pcb_dbg_regs.dbg_flags & DBGMON_ENABLED) != 0) {
		/* Disable the user breakpoints until we return to userspace */
		for (i = 0; i < dbg_watchpoint_num; i++) {
			dbg_wb_write_reg(DBG_REG_BASE_WCR, i, 0);
			dbg_wb_write_reg(DBG_REG_BASE_WVR, i, 0);
		}

		for (i = 0; i < dbg_breakpoint_num; ++i) {
			dbg_wb_write_reg(DBG_REG_BASE_BCR, i, 0);
			dbg_wb_write_reg(DBG_REG_BASE_BVR, i, 0);
		}
		WRITE_SPECIALREG(mdscr_el1,
		    READ_SPECIALREG(mdscr_el1) &
		    ~(DBG_MDSCR_MDE | DBG_MDSCR_KDE));
		isb();
	}
}