#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int tmm; } ;
typedef  TYPE_2__ sli4_req_common_set_features_t10_pi_mem_model_t ;
struct TYPE_7__ {scalar_t__ dif_mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  os; TYPE_1__ config; int /*<<< orphan*/  sli; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
typedef  int /*<<< orphan*/  mode_param ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_POLL ; 
 scalar_t__ OCS_HW_DIF_MODE_INLINE ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI4_SET_FEATURES_DIF_MEMORY_MODE ; 
 scalar_t__ ocs_hw_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sli_cmd_common_set_features (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_set_dif_mode(ocs_hw_t *hw)
{
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;
	uint8_t buf[SLI4_BMBX_SIZE];
	sli4_req_common_set_features_t10_pi_mem_model_t mode_param;

	ocs_memset(&mode_param, 0, sizeof(mode_param));
	mode_param.tmm = (hw->config.dif_mode == OCS_HW_DIF_MODE_INLINE ? 0 : 1);

	/* send set_features command */
	if (sli_cmd_common_set_features(&hw->sli, buf, SLI4_BMBX_SIZE,
					SLI4_SET_FEATURES_DIF_MEMORY_MODE,
					sizeof(mode_param),
					(uint32_t*)&mode_param)) {
		rc = ocs_hw_command(hw, buf, OCS_CMD_POLL, NULL, NULL);
		if (rc) {
			ocs_log_err(hw->os, "ocs_hw_command returns %d\n", rc);
		} else {
			ocs_log_test(hw->os, "DIF mode set to %s\n",
				(hw->config.dif_mode == OCS_HW_DIF_MODE_INLINE ? "inline" : "separate"));
		}
	} else {
		ocs_log_err(hw->os, "sli_cmd_common_set_features failed\n");
		rc = OCS_HW_RTN_ERROR;
	}
	return rc;
}