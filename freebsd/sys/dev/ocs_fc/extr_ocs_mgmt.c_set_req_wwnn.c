#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  xport; } ;
typedef  TYPE_1__ ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_XPORT_PORT_OFFLINE ; 
 int /*<<< orphan*/  OCS_XPORT_PORT_ONLINE ; 
 int /*<<< orphan*/  OCS_XPORT_WWNN_SET ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,...) ; 
 scalar_t__ ocs_strcasecmp (char*,char*) ; 
 int ocs_xport_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ parse_wwn (char*,scalar_t__*) ; 

int
set_req_wwnn(ocs_t *ocs, char *name, char *value)
{
	int rc;
	uint64_t wwnn;

	if (ocs_strcasecmp(value, "default") == 0) {
		wwnn = 0;
	}
	else if (parse_wwn(value, &wwnn) != 0) {
		ocs_log_test(ocs, "Invalid WWNN: %s\n", value);
		return 1;
	}

	rc = ocs_xport_control(ocs->xport, OCS_XPORT_WWNN_SET, wwnn);

	if(rc) {
		ocs_log_test(ocs, "OCS_XPORT_WWNN_SET failed: %d\n", rc);
		return rc;
	}

	rc = ocs_xport_control(ocs->xport, OCS_XPORT_PORT_OFFLINE);
	if (rc) {
		ocs_log_test(ocs, "port offline failed : %d\n", rc);
	}

	rc = ocs_xport_control(ocs->xport, OCS_XPORT_PORT_ONLINE);
	if (rc) {
		ocs_log_test(ocs, "port online failed : %d\n", rc);
	}

	return rc;
}