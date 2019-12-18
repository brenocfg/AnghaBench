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
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
typedef  int /*<<< orphan*/  ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RD ; 
 int /*<<< orphan*/  OCS_SCSI_PORTNUM ; 
 int /*<<< orphan*/  ocs_mgmt_emit_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 char* ocs_scsi_get_property_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_phy_port_num(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	char *phy_port = NULL;

	phy_port = ocs_scsi_get_property_ptr(ocs, OCS_SCSI_PORTNUM);
	if (phy_port) {
		ocs_mgmt_emit_string(textbuf, MGMT_MODE_RD, "phy_port_num", phy_port);
	} else {
		ocs_mgmt_emit_string(textbuf, MGMT_MODE_RD, "phy_port_num", "unknown");
	}
}