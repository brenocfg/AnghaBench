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
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint64_t ;
typedef  int u_int ;
struct debug_monitor_state {int dbg_flags; int* dbg_wcr; int /*<<< orphan*/  dbg_enable_count; int /*<<< orphan*/ * dbg_wvr; } ;
typedef  enum dbg_access_t { ____Placeholder_dbg_access_t } dbg_access_t ;

/* Variables and functions */
 int DBGMON_ENABLED ; 
 int DBGMON_KERNEL ; 
 int /*<<< orphan*/  DBG_TYPE_WATCHPOINT ; 
 int DBG_WATCH_CTRL_EXEC ; 
 int DBG_WATCH_CTRL_LEN_1 ; 
 int DBG_WATCH_CTRL_LEN_2 ; 
 int DBG_WATCH_CTRL_LEN_4 ; 
 int DBG_WATCH_CTRL_LEN_8 ; 
 int DBG_WATCH_CTRL_LOAD ; 
 int DBG_WATCH_CTRL_STORE ; 
 int DBG_WB_CTRL_E ; 
 int DBG_WB_CTRL_EL0 ; 
 int DBG_WB_CTRL_EL1 ; 
#define  HW_BREAKPOINT_R 131 
#define  HW_BREAKPOINT_RW 130 
#define  HW_BREAKPOINT_W 129 
#define  HW_BREAKPOINT_X 128 
 int dbg_find_free_slot (struct debug_monitor_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_register_sync (struct debug_monitor_state*) ; 
 int dbg_watchpoint_num ; 
 struct debug_monitor_state kernel_monitor ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
dbg_setup_watchpoint(struct debug_monitor_state *monitor, vm_offset_t addr,
    vm_size_t size, enum dbg_access_t access)
{
	uint64_t wcr_size, wcr_priv, wcr_access;
	u_int i;

	if (monitor == NULL)
		monitor = &kernel_monitor;

	i = dbg_find_free_slot(monitor, DBG_TYPE_WATCHPOINT);
	if (i == -1) {
		printf("Can not find slot for watchpoint, max %d"
		    " watchpoints supported\n", dbg_watchpoint_num);
		return (i);
	}

	switch(size) {
	case 1:
		wcr_size = DBG_WATCH_CTRL_LEN_1;
		break;
	case 2:
		wcr_size = DBG_WATCH_CTRL_LEN_2;
		break;
	case 4:
		wcr_size = DBG_WATCH_CTRL_LEN_4;
		break;
	case 8:
		wcr_size = DBG_WATCH_CTRL_LEN_8;
		break;
	default:
		printf("Unsupported address size for watchpoint\n");
		return (-1);
	}

	if ((monitor->dbg_flags & DBGMON_KERNEL) == 0)
		wcr_priv = DBG_WB_CTRL_EL0;
	else
		wcr_priv = DBG_WB_CTRL_EL1;

	switch(access) {
	case HW_BREAKPOINT_X:
		wcr_access = DBG_WATCH_CTRL_EXEC;
		break;
	case HW_BREAKPOINT_R:
		wcr_access = DBG_WATCH_CTRL_LOAD;
		break;
	case HW_BREAKPOINT_W:
		wcr_access = DBG_WATCH_CTRL_STORE;
		break;
	case HW_BREAKPOINT_RW:
		wcr_access = DBG_WATCH_CTRL_LOAD | DBG_WATCH_CTRL_STORE;
		break;
	default:
		printf("Unsupported exception level for watchpoint\n");
		return (-1);
	}

	monitor->dbg_wvr[i] = addr;
	monitor->dbg_wcr[i] = wcr_size | wcr_access | wcr_priv | DBG_WB_CTRL_E;
	monitor->dbg_enable_count++;
	monitor->dbg_flags |= DBGMON_ENABLED;

	dbg_register_sync(monitor);
	return (0);
}