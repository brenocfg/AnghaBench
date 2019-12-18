#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;

/* Variables and functions */
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_HW_TOPOLOGY ; 
 scalar_t__ OCS_HW_TOPOLOGY_NONE ; 
 int /*<<< orphan*/  OCS_XPORT_PORT_OFFLINE ; 
 int /*<<< orphan*/  OCS_XPORT_PORT_ONLINE ; 
 scalar_t__ ocs_hw_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*) ; 
 scalar_t__ ocs_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ocs_xport_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
set_configured_topology(ocs_t *ocs, char *name, char *value)
{
	int result = 0;
	ocs_hw_rtn_e hw_rc;
	int xport_rc;
	uint32_t topo;

	topo = ocs_strtoul(value, NULL, 0);
	if (topo >= OCS_HW_TOPOLOGY_NONE) {
		return 1;
	}

	ocs_log_debug(ocs, "Taking port offline\n");
	xport_rc = ocs_xport_control(ocs->xport, OCS_XPORT_PORT_OFFLINE);
	if (xport_rc != 0) {
		ocs_log_test(ocs, "Port offline failed\n");
		result = 1;
	} else {
		ocs_log_debug(ocs, "Setting port to topology %d\n", topo);
		hw_rc = ocs_hw_set(&ocs->hw, OCS_HW_TOPOLOGY, topo);
		if (hw_rc != OCS_HW_RTN_SUCCESS) {
			ocs_log_test(ocs, "Topology set failed\n");
			result = 1;
		}

		/* If we failed to set the topology we still want to try to bring
		 * the port back online */

		ocs_log_debug(ocs, "Bringing port online\n");
		xport_rc = ocs_xport_control(ocs->xport, OCS_XPORT_PORT_ONLINE);
		if (xport_rc != 0) {
			result = 1;
		}
	}

	return result;
}