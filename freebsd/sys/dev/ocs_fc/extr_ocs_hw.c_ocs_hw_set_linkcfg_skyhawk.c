#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {void* arg; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_18__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
typedef  int /*<<< orphan*/  ocs_hw_port_control_cb_t ;
typedef  int /*<<< orphan*/  ocs_hw_linkcfg_e ;
typedef  TYPE_1__ ocs_hw_linkcfg_cb_arg_t ;

/* Variables and functions */
 scalar_t__ OCS_CMD_POLL ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ ocs_hw_command (TYPE_2__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/  (*) (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*),TYPE_1__*) ; 
 scalar_t__ ocs_hw_config_id_from_linkcfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_set_active_link_config_cb (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ sli_cmd_common_set_reconfig_link_id (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_set_linkcfg_skyhawk(ocs_hw_t *hw, ocs_hw_linkcfg_e value, uint32_t opts, ocs_hw_port_control_cb_t cb, void *arg)
{
	uint8_t *mbxdata;
	ocs_hw_linkcfg_cb_arg_t *cb_arg;
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;
	uint32_t config_id;

	config_id = ocs_hw_config_id_from_linkcfg(value);

	if (config_id == 0) {
		ocs_log_test(hw->os, "Link config %d not supported by Skyhawk\n", value);
		return OCS_HW_RTN_ERROR;
	}

	/* mbxdata holds the header of the command */
	mbxdata = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_ZERO | OCS_M_NOWAIT);
	if (mbxdata == NULL) {
		ocs_log_err(hw->os, "failed to malloc mbox\n");
		return OCS_HW_RTN_NO_MEMORY;
	}

	/* cb_arg holds the data that will be passed to the callback on completion */
	cb_arg = ocs_malloc(hw->os, sizeof(ocs_hw_linkcfg_cb_arg_t), OCS_M_NOWAIT);
	if (cb_arg == NULL) {
		ocs_log_err(hw->os, "failed to malloc cb_arg\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		return OCS_HW_RTN_NO_MEMORY;
	}

	cb_arg->cb = cb;
	cb_arg->arg = arg;

	if (sli_cmd_common_set_reconfig_link_id(&hw->sli, mbxdata, SLI4_BMBX_SIZE, NULL, 0, config_id)) {
		rc = ocs_hw_command(hw, mbxdata, opts, ocs_hw_set_active_link_config_cb, cb_arg);
	}

	if (rc != OCS_HW_RTN_SUCCESS) {
		ocs_log_err(hw->os, "SET_RECONFIG_LINK_ID failed\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_linkcfg_cb_arg_t));
	} else if (opts == OCS_CMD_POLL) {
		/* if we're polling we have to call the callback here. */
		ocs_hw_set_active_link_config_cb(hw, 0, mbxdata, cb_arg);
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_linkcfg_cb_arg_t));
	} else {
		/* We weren't poling, so the callback got called */
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
	}

	return rc;
}