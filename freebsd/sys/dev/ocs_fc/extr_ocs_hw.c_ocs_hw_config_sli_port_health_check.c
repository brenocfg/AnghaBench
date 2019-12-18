#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_7__ {void* qry; void* hck; } ;
typedef  TYPE_1__ sli4_req_common_set_features_health_check_t ;
typedef  int /*<<< orphan*/  param ;
struct TYPE_8__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_POLL ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI4_SET_FEATURES_SLI_PORT_HEALTH_CHECK ; 
 scalar_t__ ocs_hw_command (TYPE_2__*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sli_cmd_common_set_features (int /*<<< orphan*/ *,void**,int,int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_config_sli_port_health_check(ocs_hw_t *hw, uint8_t query, uint8_t enable)
{
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;
	uint8_t buf[SLI4_BMBX_SIZE];
	sli4_req_common_set_features_health_check_t param;

	ocs_memset(&param, 0, sizeof(param));
	param.hck = enable;
	param.qry = query;

	/* build the set_features command */
	sli_cmd_common_set_features(&hw->sli, buf, SLI4_BMBX_SIZE,
				    SLI4_SET_FEATURES_SLI_PORT_HEALTH_CHECK,
				    sizeof(param),
				    &param);

	rc = ocs_hw_command(hw, buf, OCS_CMD_POLL, NULL, NULL);
	if (rc) {
		ocs_log_err(hw->os, "ocs_hw_command returns %d\n", rc);
	} else {
		ocs_log_test(hw->os, "SLI Port Health Check is enabled \n");
	}

	return rc;
}