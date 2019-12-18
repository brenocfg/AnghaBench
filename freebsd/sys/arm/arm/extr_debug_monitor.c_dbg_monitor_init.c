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

/* Variables and functions */
 scalar_t__ ID_DFR0_CP_DEBUG_M_V6 ; 
 scalar_t__ ID_DFR0_CP_DEBUG_M_V6_1 ; 
 scalar_t__ ID_DFR0_CP_DEBUG_M_V7 ; 
 scalar_t__ ID_DFR0_CP_DEBUG_M_V7_1 ; 
 char* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  dbg_arch_supported () ; 
 int /*<<< orphan*/  dbg_breakpoint_num ; 
 int /*<<< orphan*/  dbg_capable_var ; 
 int dbg_enable_monitor () ; 
 scalar_t__ dbg_get_debug_model () ; 
 int /*<<< orphan*/  dbg_get_ossr () ; 
 int /*<<< orphan*/  dbg_get_wrp_num () ; 
 scalar_t__ dbg_model ; 
 int /*<<< orphan*/  dbg_ossr ; 
 int dbg_reset_state () ; 
 int /*<<< orphan*/  dbg_watchpoint_num ; 
 int /*<<< orphan*/  dgb_get_brp_num () ; 

void
dbg_monitor_init(void)
{
	int err;

	/* Fetch ARM Debug Architecture model */
	dbg_model = dbg_get_debug_model();

	if (!dbg_arch_supported()) {
		db_printf("ARM Debug Architecture not supported\n");
		return;
	}

	if (bootverbose) {
		db_printf("ARM Debug Architecture %s\n",
		    (dbg_model == ID_DFR0_CP_DEBUG_M_V6) ? "v6" :
		    (dbg_model == ID_DFR0_CP_DEBUG_M_V6_1) ? "v6.1" :
		    (dbg_model == ID_DFR0_CP_DEBUG_M_V7) ? "v7" :
		    (dbg_model == ID_DFR0_CP_DEBUG_M_V7_1) ? "v7.1" : "unknown");
	}

	/* Do we have OS Save and Restore mechanism? */
	dbg_ossr = dbg_get_ossr();

	/* Find out many breakpoints and watchpoints we can use */
	dbg_watchpoint_num = dbg_get_wrp_num();
	dbg_breakpoint_num = dgb_get_brp_num();

	if (bootverbose) {
		db_printf("%d watchpoints and %d breakpoints supported\n",
		    dbg_watchpoint_num, dbg_breakpoint_num);
	}

	err = dbg_reset_state();
	if (err == 0) {
		err = dbg_enable_monitor();
		if (err == 0) {
			atomic_set_int(&dbg_capable_var, 1);
			return;
		}
	}

	db_printf("HW Breakpoints/Watchpoints not enabled on CPU%d\n",
	    PCPU_GET(cpuid));
}