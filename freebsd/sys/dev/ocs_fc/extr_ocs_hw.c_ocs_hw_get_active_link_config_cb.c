#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  active_link_config_id; } ;
typedef  TYPE_1__ sli4_res_common_get_reconfig_link_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_linkcfg_e ;
struct TYPE_10__ {TYPE_1__* virt; } ;
struct TYPE_9__ {scalar_t__ opts; TYPE_6__ dma_cmd; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ ocs_hw_linkcfg_cb_arg_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ OCS_CMD_POLL ; 
 int /*<<< orphan*/  OCS_HW_LINKCFG_NA ; 
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ocs_hw_linkcfg_from_config_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_hw_get_active_link_config_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{
	ocs_hw_linkcfg_cb_arg_t *cb_arg = (ocs_hw_linkcfg_cb_arg_t *)arg;
	sli4_res_common_get_reconfig_link_info_t *rsp = cb_arg->dma_cmd.virt;
	ocs_hw_linkcfg_e value = OCS_HW_LINKCFG_NA;

	if (status) {
		ocs_log_test(hw->os, "GET_RECONFIG_LINK_INFO failed, status=%d\n", status);
	} else {
		/* Call was successful */
		value = ocs_hw_linkcfg_from_config_id(rsp->active_link_config_id);
	}

	/* invoke callback */
	if (cb_arg->cb) {
		cb_arg->cb(status, value, cb_arg->arg);
	}

	/* if polling, will free memory in calling function */
	if (cb_arg->opts != OCS_CMD_POLL) {
		ocs_dma_free(hw->os, &cb_arg->dma_cmd);
		ocs_free(hw->os, cb_arg, sizeof(*cb_arg));
	}
}