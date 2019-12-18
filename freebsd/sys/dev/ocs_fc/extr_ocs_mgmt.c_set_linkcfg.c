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
struct TYPE_7__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_8__ {scalar_t__ status; int /*<<< orphan*/  semaphore; } ;
typedef  TYPE_2__ ocs_mgmt_linkcfg_arg_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
typedef  scalar_t__ ocs_hw_linkcfg_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_PORT_SET_LINK_CONFIG ; 
 int /*<<< orphan*/  OCS_SEM_FOREVER ; 
 scalar_t__ ocs_hw_linkcfg_from_mgmt (char*) ; 
 scalar_t__ ocs_hw_port_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  ocs_mgmt_linkcfg_cb ; 
 int /*<<< orphan*/  ocs_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ocs_sem_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_linkcfg(ocs_t *ocs, char *name, char *value)
{
	ocs_hw_linkcfg_e linkcfg;
	ocs_mgmt_linkcfg_arg_t cb_arg;
	ocs_hw_rtn_e status;

	ocs_sem_init(&cb_arg.semaphore, 0, "mgmt_linkcfg");

	/* translate mgmt linkcfg string to HW linkcfg enum */
	linkcfg = ocs_hw_linkcfg_from_mgmt(value);

	/* set HW linkcfg */
	status = ocs_hw_port_control(&ocs->hw, OCS_HW_PORT_SET_LINK_CONFIG,
				      (uintptr_t)linkcfg, ocs_mgmt_linkcfg_cb, &cb_arg);
	if (status) {
		ocs_log_test(ocs, "ocs_hw_set_linkcfg failed\n");
		return -1;
	}

	if (ocs_sem_p(&cb_arg.semaphore, OCS_SEM_FOREVER)) {
		ocs_log_err(ocs, "ocs_sem_p failed\n");
		return -1;
	}

	if (cb_arg.status) {
		ocs_log_test(ocs, "failed to set linkcfg from HW status=%d\n",
			     cb_arg.status);
		return -1;
	}

	return 0;
}