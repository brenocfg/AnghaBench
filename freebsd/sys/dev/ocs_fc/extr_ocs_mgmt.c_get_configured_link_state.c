#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ value; } ;
typedef  TYPE_1__ ocs_xport_stats_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_6__ {int /*<<< orphan*/  xport; } ;
typedef  TYPE_2__ ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RW ; 
 int /*<<< orphan*/  OCS_XPORT_CONFIG_PORT_STATUS ; 
 scalar_t__ OCS_XPORT_PORT_ONLINE ; 
 int /*<<< orphan*/  ocs_mgmt_emit_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ocs_xport_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
get_configured_link_state(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	ocs_xport_stats_t value;

	if (ocs_xport_status(ocs->xport, OCS_XPORT_CONFIG_PORT_STATUS, &value) == 0) {
		if (value.value == OCS_XPORT_PORT_ONLINE) {
			ocs_mgmt_emit_string(textbuf, MGMT_MODE_RW, "configured_link_state", "online");
		} else {
			ocs_mgmt_emit_string(textbuf, MGMT_MODE_RW, "configured_link_state", "offline");
		}
	}
}