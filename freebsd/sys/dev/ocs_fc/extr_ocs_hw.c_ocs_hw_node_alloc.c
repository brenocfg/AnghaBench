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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_sli_port_t ;
struct TYPE_5__ {scalar_t__ indicator; int /*<<< orphan*/ * sport; int /*<<< orphan*/  fc_id; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ ocs_remote_node_t ;
struct TYPE_6__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_RPI ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ sli_fw_error_status (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_resource_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_node_alloc(ocs_hw_t *hw, ocs_remote_node_t *rnode, uint32_t fc_addr,
		ocs_sli_port_t *sport)
{
	/* Check for invalid indicator */
	if (UINT32_MAX != rnode->indicator) {
		ocs_log_err(hw->os, "FCOE_RPI allocation failure addr=%#x rpi=%#x\n",
				fc_addr, rnode->indicator);
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Check if the chip is in an error state (UE'd) before proceeding.
	 */
	if (sli_fw_error_status(&hw->sli) > 0) {
		ocs_log_crit(hw->os, "Chip is in an error state - reset needed\n");
		return OCS_HW_RTN_ERROR;
	}

	/* NULL SLI port indicates an unallocated remote node */
	rnode->sport = NULL;

	if (sli_resource_alloc(&hw->sli, SLI_RSRC_FCOE_RPI, &rnode->indicator, &rnode->index)) {
		ocs_log_err(hw->os, "FCOE_RPI allocation failure addr=%#x\n",
				fc_addr);
		return OCS_HW_RTN_ERROR;
	}

	rnode->fc_id = fc_addr;
	rnode->sport = sport;

	return OCS_HW_RTN_SUCCESS;
}