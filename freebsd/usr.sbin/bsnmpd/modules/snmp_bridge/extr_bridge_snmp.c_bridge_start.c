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
 void* bridge_data_timer ; 
 int /*<<< orphan*/  bridge_module ; 
 int /*<<< orphan*/  bridge_poll_ticks ; 
 int /*<<< orphan*/  bridge_tc_poll_ticks ; 
 void* bridge_tc_timer ; 
 int /*<<< orphan*/  bridge_update_all ; 
 int /*<<< orphan*/  bridge_update_tc_time ; 
 int /*<<< orphan*/  oid_dot1Bridge ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_bridge ; 
 void* timer_start_repeat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bridge_start(void)
{
	reg_bridge = or_register(&oid_dot1Bridge,
	    "The IETF MIB for Bridges (RFC 4188).", bridge_module);

	bridge_data_timer = timer_start_repeat(bridge_poll_ticks,
	    bridge_poll_ticks, bridge_update_all, NULL, bridge_module);

	bridge_tc_timer = timer_start_repeat(bridge_tc_poll_ticks,
	    bridge_tc_poll_ticks, bridge_update_tc_time, NULL, bridge_module);
}