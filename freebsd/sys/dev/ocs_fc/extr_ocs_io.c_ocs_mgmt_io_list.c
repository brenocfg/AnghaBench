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

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RD ; 
 int /*<<< orphan*/  ocs_mgmt_emit_property_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
ocs_mgmt_io_list(ocs_textbuf_t *textbuf, void *object)
{

	/* Readonly values */
	ocs_mgmt_emit_property_name(textbuf, MGMT_MODE_RD, "display_name");
	ocs_mgmt_emit_property_name(textbuf, MGMT_MODE_RD, "init_task_tag");
	ocs_mgmt_emit_property_name(textbuf, MGMT_MODE_RD, "tag");
	ocs_mgmt_emit_property_name(textbuf, MGMT_MODE_RD, "transferred");
	ocs_mgmt_emit_property_name(textbuf, MGMT_MODE_RD, "auto_resp");
	ocs_mgmt_emit_property_name(textbuf, MGMT_MODE_RD, "exp_xfer_len");
	ocs_mgmt_emit_property_name(textbuf, MGMT_MODE_RD, "xfer_req");
}