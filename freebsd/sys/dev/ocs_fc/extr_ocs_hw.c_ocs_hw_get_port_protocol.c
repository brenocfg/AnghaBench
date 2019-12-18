#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  payload; int /*<<< orphan*/  pci_func; void* arg; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
typedef  TYPE_1__ ocs_hw_get_port_protocol_cb_arg_t ;
typedef  int /*<<< orphan*/  ocs_hw_fw_write_cb_arg_t ;
typedef  int /*<<< orphan*/  ocs_get_port_protocol_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int SLI4_BMBX_SIZE ; 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_PF ; 
 scalar_t__ ocs_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ ocs_hw_command (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_get_port_protocol_cb ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ sli_cmd_common_get_profile_config (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sli_get_if_type (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_get_port_protocol(ocs_hw_t *hw, uint32_t pci_func,
	ocs_get_port_protocol_cb_t cb, void* ul_arg)
{
	uint8_t *mbxdata;
	ocs_hw_get_port_protocol_cb_arg_t *cb_arg;
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;

	/* Only supported on Skyhawk */
	if (sli_get_if_type(&hw->sli) != SLI4_IF_TYPE_BE3_SKH_PF) {
		return OCS_HW_RTN_ERROR;
	}

	/* mbxdata holds the header of the command */
	mbxdata = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_ZERO | OCS_M_NOWAIT);
	if (mbxdata == NULL) {
		ocs_log_err(hw->os, "failed to malloc mbox\n");
		return OCS_HW_RTN_NO_MEMORY;
	}


	/* cb_arg holds the data that will be passed to the callback on completion */
	cb_arg = ocs_malloc(hw->os, sizeof(ocs_hw_get_port_protocol_cb_arg_t), OCS_M_NOWAIT);
	if (cb_arg == NULL) {
		ocs_log_err(hw->os, "failed to malloc cb_arg\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		return OCS_HW_RTN_NO_MEMORY;
	}

	cb_arg->cb = cb;
	cb_arg->arg = ul_arg;
	cb_arg->pci_func = pci_func;

	/* dma_mem holds the non-embedded portion */
	if (ocs_dma_alloc(hw->os, &cb_arg->payload, 4096, 4)) {
		ocs_log_err(hw->os, "Failed to allocate DMA buffer\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_get_port_protocol_cb_arg_t));
		return OCS_HW_RTN_NO_MEMORY;
	}

	if (sli_cmd_common_get_profile_config(&hw->sli, mbxdata, SLI4_BMBX_SIZE, &cb_arg->payload)) {
		rc = ocs_hw_command(hw, mbxdata, OCS_CMD_NOWAIT, ocs_hw_get_port_protocol_cb, cb_arg);
	}

	if (rc != OCS_HW_RTN_SUCCESS) {
		ocs_log_test(hw->os, "GET_PROFILE_CONFIG failed\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_fw_write_cb_arg_t));
		ocs_dma_free(hw->os, &cb_arg->payload);
	}

	return rc;

}