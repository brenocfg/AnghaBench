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
 int /*<<< orphan*/  bridge_addrs_fini () ; 
 int /*<<< orphan*/ * bridge_data_timer ; 
 int /*<<< orphan*/  bridge_ifs_fini () ; 
 int /*<<< orphan*/  bridge_module ; 
 int /*<<< orphan*/  bridge_ports_fini () ; 
 int /*<<< orphan*/ * bridge_tc_timer ; 
 int /*<<< orphan*/  mib_unregister_newif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  or_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_bridge ; 
 int /*<<< orphan*/  timer_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bridge_fini(void)
{
	mib_unregister_newif(bridge_module);
	or_unregister(reg_bridge);

	if (bridge_data_timer != NULL) {
		timer_stop(bridge_data_timer);
		bridge_data_timer = NULL;
	}

	if (bridge_tc_timer != NULL) {
		timer_stop(bridge_tc_timer);
		bridge_tc_timer = NULL;
	}

	bridge_ifs_fini();
	bridge_ports_fini();
	bridge_addrs_fini();

	return (0);
}