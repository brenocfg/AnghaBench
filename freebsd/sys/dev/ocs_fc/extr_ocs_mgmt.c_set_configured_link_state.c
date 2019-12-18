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
struct TYPE_5__ {int /*<<< orphan*/  xport; } ;
typedef  TYPE_1__ ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_XPORT_PORT_OFFLINE ; 
 int /*<<< orphan*/  OCS_XPORT_PORT_ONLINE ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,...) ; 
 scalar_t__ ocs_strcasecmp (char*,char*) ; 
 int ocs_xport_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_configured_link_state(ocs_t *ocs, char *name, char *value)
{
	int result = 0;
	int xport_rc;

	if (ocs_strcasecmp(value, "offline") == 0) {
		ocs_log_debug(ocs, "Setting port to %s\n", value);
		xport_rc = ocs_xport_control(ocs->xport, OCS_XPORT_PORT_OFFLINE);
		if (xport_rc != 0) {
			ocs_log_test(ocs, "Setting port to offline failed\n");
			result = -1;
		}
	} else if (ocs_strcasecmp(value, "online") == 0) {
		ocs_log_debug(ocs, "Setting port to %s\n", value);
		xport_rc = ocs_xport_control(ocs->xport, OCS_XPORT_PORT_ONLINE);
		if (xport_rc != 0) {
			ocs_log_test(ocs, "Setting port to online failed\n");
			result = -1;
		}
	} else {
		ocs_log_test(ocs, "Unsupported link state \"%s\"\n", value);
		result = -1;
	}

	return result;
}