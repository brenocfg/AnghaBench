#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_9__ {size_t index; int fc_id; int /*<<< orphan*/  indicator; int /*<<< orphan*/  free_group; scalar_t__ node_group; int /*<<< orphan*/  attached; scalar_t__ sport; } ;
typedef  TYPE_2__ ocs_remote_node_t ;
struct TYPE_10__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; TYPE_1__* rpi_ref; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
struct TYPE_8__ {int /*<<< orphan*/  rpi_count; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 scalar_t__ OCS_HW_RTN_SUCCESS_SYNC ; 
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_RPI ; 
 int /*<<< orphan*/  TRUE ; 
 size_t UINT32_MAX ; 
 size_t ocs_atomic_sub_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_cb_node_free ; 
 scalar_t__ ocs_hw_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * ocs_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_cmd_unreg_rpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sli_fw_error_status (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_get_hlm (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_node_detach(ocs_hw_t *hw, ocs_remote_node_t *rnode)
{
	uint8_t	*buf = NULL;
	ocs_hw_rtn_e	rc = OCS_HW_RTN_SUCCESS_SYNC;
	uint32_t	index = UINT32_MAX;

	if (!hw || !rnode) {
		ocs_log_err(NULL, "bad parameter(s) hw=%p rnode=%p\n",
			    hw, rnode);
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Check if the chip is in an error state (UE'd) before proceeding.
	 */
	if (sli_fw_error_status(&hw->sli) > 0) {
		ocs_log_crit(hw->os, "Chip is in an error state - reset needed\n");
		return OCS_HW_RTN_ERROR;
	}

	index = rnode->index;

	if (rnode->sport) {
		uint32_t	count = 0;
		uint32_t	fc_id;

		if (!rnode->attached) {
			return OCS_HW_RTN_SUCCESS_SYNC;
		}

		buf = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
		if (!buf) {
			ocs_log_err(hw->os, "no buffer for command\n");
			return OCS_HW_RTN_NO_MEMORY;
		}

		count = ocs_atomic_sub_return(&hw->rpi_ref[index].rpi_count, 1);

		if (count <= 1) {
			/* There are no other references to this RPI
			 * so unregister it and free the resource. */
			fc_id = UINT32_MAX;
			rnode->node_group = FALSE;
			rnode->free_group = TRUE;
		} else {
			if (sli_get_hlm(&hw->sli) == FALSE) {
				ocs_log_test(hw->os, "Invalid count with HLM disabled, count=%d\n",
						count);
			}
			fc_id = rnode->fc_id & 0x00ffffff;
		}

		rc = OCS_HW_RTN_ERROR;

		if (sli_cmd_unreg_rpi(&hw->sli, buf, SLI4_BMBX_SIZE, rnode->indicator,
					SLI_RSRC_FCOE_RPI, fc_id)) {
			rc = ocs_hw_command(hw, buf, OCS_CMD_NOWAIT, ocs_hw_cb_node_free, rnode);
		}

		if (rc != OCS_HW_RTN_SUCCESS) {
			ocs_log_err(hw->os, "UNREG_RPI failed\n");
			ocs_free(hw->os, buf, SLI4_BMBX_SIZE);
			rc = OCS_HW_RTN_ERROR;
		}
	}

	return rc;
}