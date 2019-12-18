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
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  RFHIGHPID ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_FIRST ; 
 int /*<<< orphan*/  g_ctl_init () ; 
 int /*<<< orphan*/  g_down_procbody ; 
 int /*<<< orphan*/  g_down_td ; 
 int /*<<< orphan*/  g_event_init () ; 
 int /*<<< orphan*/  g_event_procbody ; 
 int /*<<< orphan*/  g_event_td ; 
 int /*<<< orphan*/  g_io_init () ; 
 int /*<<< orphan*/  g_proc ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_up_procbody ; 
 int /*<<< orphan*/  g_up_td ; 
 int /*<<< orphan*/  geom_shutdown ; 
 int /*<<< orphan*/  kproc_kthread_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  topology_lock ; 

void
g_init(void)
{

	g_trace(G_T_TOPOLOGY, "g_ignition");
	sx_init(&topology_lock, "GEOM topology");
	g_io_init();
	g_event_init();
	g_ctl_init();
	kproc_kthread_add(g_event_procbody, NULL, &g_proc, &g_event_td,
	    RFHIGHPID, 0, "geom", "g_event");
	kproc_kthread_add(g_up_procbody, NULL, &g_proc, &g_up_td,
	    RFHIGHPID, 0, "geom", "g_up");
	kproc_kthread_add(g_down_procbody, NULL, &g_proc, &g_down_td,
	    RFHIGHPID, 0, "geom", "g_down");
	EVENTHANDLER_REGISTER(shutdown_pre_sync, geom_shutdown, NULL,
		SHUTDOWN_PRI_FIRST);
}