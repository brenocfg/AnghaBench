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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  ifnet_departure_event ; 
 int /*<<< orphan*/  lagg_detach_cookie ; 
 int /*<<< orphan*/ * lagg_input ; 
 int /*<<< orphan*/ * lagg_input_p ; 
 int /*<<< orphan*/ * lagg_linkstate_p ; 
 int /*<<< orphan*/  lagg_port_ifdetach ; 
 int /*<<< orphan*/ * lagg_port_state ; 

__attribute__((used)) static int
lagg_modevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		lagg_input_p = lagg_input;
		lagg_linkstate_p = lagg_port_state;
		lagg_detach_cookie = EVENTHANDLER_REGISTER(
		    ifnet_departure_event, lagg_port_ifdetach, NULL,
		    EVENTHANDLER_PRI_ANY);
		break;
	case MOD_UNLOAD:
		EVENTHANDLER_DEREGISTER(ifnet_departure_event,
		    lagg_detach_cookie);
		lagg_input_p = NULL;
		lagg_linkstate_p = NULL;
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}