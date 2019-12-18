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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int ;
struct debug_monitor_state {scalar_t__ dbg_enable_count; int /*<<< orphan*/  dbg_flags; scalar_t__* dbg_wcr; scalar_t__* dbg_wvr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMON_ENABLED ; 
 int /*<<< orphan*/  DBG_TYPE_WATCHPOINT ; 
 int dbg_find_slot (struct debug_monitor_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_register_sync (struct debug_monitor_state*) ; 
 struct debug_monitor_state kernel_monitor ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

int
dbg_remove_watchpoint(struct debug_monitor_state *monitor, vm_offset_t addr,
    vm_size_t size)
{
	u_int i;

	if (monitor == NULL)
		monitor = &kernel_monitor;

	i = dbg_find_slot(monitor, DBG_TYPE_WATCHPOINT, addr);
	if (i == -1) {
		printf("Can not find watchpoint for address 0%lx\n", addr);
		return (i);
	}

	monitor->dbg_wvr[i] = 0;
	monitor->dbg_wcr[i] = 0;
	monitor->dbg_enable_count--;
	if (monitor->dbg_enable_count == 0)
		monitor->dbg_flags &= ~DBGMON_ENABLED;

	dbg_register_sync(monitor);
	return (0);
}