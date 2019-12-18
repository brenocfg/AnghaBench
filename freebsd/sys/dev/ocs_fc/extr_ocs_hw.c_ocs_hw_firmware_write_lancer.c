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
struct TYPE_11__ {void* arg; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
typedef  TYPE_1__ ocs_hw_fw_write_cb_arg_t ;
typedef  int /*<<< orphan*/  ocs_hw_fw_cb_t ;
typedef  int /*<<< orphan*/  ocs_dma_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int SLI4_BMBX_SIZE ; 
 scalar_t__ SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ocs_hw_cb_fw_write ; 
 scalar_t__ ocs_hw_command (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ sli_cmd_common_write_object (int /*<<< orphan*/ *,TYPE_1__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sli_get_if_type (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_firmware_write_lancer(ocs_hw_t *hw, ocs_dma_t *dma, uint32_t size, uint32_t offset, int last, ocs_hw_fw_cb_t cb, void *arg)
{
	ocs_hw_rtn_e rc = OCS_HW_RTN_ERROR;
	uint8_t *mbxdata;
	ocs_hw_fw_write_cb_arg_t *cb_arg;
	int noc=0;	/* No Commit bit - set to 1 for testing */

	if (SLI4_IF_TYPE_LANCER_FC_ETH != sli_get_if_type(&hw->sli)) {
		ocs_log_test(hw->os, "Function only supported for I/F type 2\n");
		return OCS_HW_RTN_ERROR;
	}

	mbxdata = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_ZERO | OCS_M_NOWAIT);
	if (mbxdata == NULL) {
		ocs_log_err(hw->os, "failed to malloc mbox\n");
		return OCS_HW_RTN_NO_MEMORY;
	}

	cb_arg = ocs_malloc(hw->os, sizeof(ocs_hw_fw_write_cb_arg_t), OCS_M_NOWAIT);
	if (cb_arg == NULL) {
		ocs_log_err(hw->os, "failed to malloc cb_arg\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		return OCS_HW_RTN_NO_MEMORY;
	}

	cb_arg->cb = cb;
	cb_arg->arg = arg;

	if (sli_cmd_common_write_object(&hw->sli, mbxdata, SLI4_BMBX_SIZE, noc, last,
			size, offset, "/prg/", dma)) {
		rc = ocs_hw_command(hw, mbxdata, OCS_CMD_NOWAIT, ocs_hw_cb_fw_write, cb_arg);
	}

	if (rc != OCS_HW_RTN_SUCCESS) {
		ocs_log_test(hw->os, "COMMON_WRITE_OBJECT failed\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_fw_write_cb_arg_t));
	}

	return rc;

}