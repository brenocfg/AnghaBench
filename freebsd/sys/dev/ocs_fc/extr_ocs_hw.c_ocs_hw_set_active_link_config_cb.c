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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_6__ {scalar_t__ opts; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ ocs_hw_linkcfg_cb_arg_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ OCS_CMD_POLL ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_hw_set_active_link_config_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{
	ocs_hw_linkcfg_cb_arg_t *cb_arg = (ocs_hw_linkcfg_cb_arg_t *)arg;

	if (status) {
		ocs_log_test(hw->os, "SET_RECONFIG_LINK_ID failed, status=%d\n", status);
	}

	/* invoke callback */
	if (cb_arg->cb) {
		cb_arg->cb(status, 0, cb_arg->arg);
	}

	/* if polling, will free memory in calling function */
	if (cb_arg->opts != OCS_CMD_POLL) {
		ocs_free(hw->os, cb_arg, sizeof(*cb_arg));
	}
}