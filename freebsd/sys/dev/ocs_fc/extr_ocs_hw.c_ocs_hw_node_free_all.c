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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_FCFI ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_cb_node_free_all ; 
 scalar_t__ ocs_hw_command (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ocs_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_cmd_unreg_rpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_fw_error_status (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_node_free_all(ocs_hw_t *hw)
{
	uint8_t	*buf = NULL;
	ocs_hw_rtn_e	rc = OCS_HW_RTN_ERROR;

	if (!hw) {
		ocs_log_err(NULL, "bad parameter hw=%p\n", hw);
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Check if the chip is in an error state (UE'd) before proceeding.
	 */
	if (sli_fw_error_status(&hw->sli) > 0) {
		ocs_log_crit(hw->os, "Chip is in an error state - reset needed\n");
		return OCS_HW_RTN_ERROR;
	}

	buf = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
	if (!buf) {
		ocs_log_err(hw->os, "no buffer for command\n");
		return OCS_HW_RTN_NO_MEMORY;
	}

	if (sli_cmd_unreg_rpi(&hw->sli, buf, SLI4_BMBX_SIZE, 0xffff,
				SLI_RSRC_FCOE_FCFI, UINT32_MAX)) {
		rc = ocs_hw_command(hw, buf, OCS_CMD_NOWAIT, ocs_hw_cb_node_free_all,
				NULL);
	}

	if (rc != OCS_HW_RTN_SUCCESS) {
		ocs_log_err(hw->os, "UNREG_RPI failed\n");
		ocs_free(hw->os, buf, SLI4_BMBX_SIZE);
		rc = OCS_HW_RTN_ERROR;
	}

	return rc;
}