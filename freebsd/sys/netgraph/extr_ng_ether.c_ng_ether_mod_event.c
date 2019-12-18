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
 int EEXIST ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  ifnet_arrival_event ; 
 int /*<<< orphan*/ * ng_ether_attach ; 
 int /*<<< orphan*/ * ng_ether_attach_p ; 
 int /*<<< orphan*/ * ng_ether_detach ; 
 int /*<<< orphan*/ * ng_ether_detach_p ; 
 int /*<<< orphan*/  ng_ether_ifnet_arrival_cookie ; 
 int /*<<< orphan*/  ng_ether_ifnet_arrival_event ; 
 int /*<<< orphan*/ * ng_ether_input ; 
 int /*<<< orphan*/ * ng_ether_input_orphan ; 
 int /*<<< orphan*/ * ng_ether_input_orphan_p ; 
 int /*<<< orphan*/ * ng_ether_input_p ; 
 int /*<<< orphan*/ * ng_ether_link_state ; 
 int /*<<< orphan*/ * ng_ether_link_state_p ; 
 int /*<<< orphan*/ * ng_ether_output ; 
 int /*<<< orphan*/ * ng_ether_output_p ; 

__attribute__((used)) static int
ng_ether_mod_event(module_t mod, int event, void *data)
{
	int error = 0;

	switch (event) {
	case MOD_LOAD:

		/* Register function hooks */
		if (ng_ether_attach_p != NULL) {
			error = EEXIST;
			break;
		}
		ng_ether_attach_p = ng_ether_attach;
		ng_ether_detach_p = ng_ether_detach;
		ng_ether_output_p = ng_ether_output;
		ng_ether_input_p = ng_ether_input;
		ng_ether_input_orphan_p = ng_ether_input_orphan;
		ng_ether_link_state_p = ng_ether_link_state;

		ng_ether_ifnet_arrival_cookie =
		    EVENTHANDLER_REGISTER(ifnet_arrival_event,
		    ng_ether_ifnet_arrival_event, NULL, EVENTHANDLER_PRI_ANY);
		break;

	case MOD_UNLOAD:

		/*
		 * Note that the base code won't try to unload us until
		 * all nodes have been removed, and that can't happen
		 * until all Ethernet interfaces are removed. In any
		 * case, we know there are no nodes left if the action
		 * is MOD_UNLOAD, so there's no need to detach any nodes.
		 */

		EVENTHANDLER_DEREGISTER(ifnet_arrival_event,
		    ng_ether_ifnet_arrival_cookie);

		/* Unregister function hooks */
		ng_ether_attach_p = NULL;
		ng_ether_detach_p = NULL;
		ng_ether_output_p = NULL;
		ng_ether_input_p = NULL;
		ng_ether_input_orphan_p = NULL;
		ng_ether_link_state_p = NULL;
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}