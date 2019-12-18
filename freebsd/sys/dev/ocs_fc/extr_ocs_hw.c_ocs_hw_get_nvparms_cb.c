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
struct TYPE_8__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  preferred_d_id; int /*<<< orphan*/  hard_alpa; int /*<<< orphan*/  wwnn; int /*<<< orphan*/  wwpn; } ;
typedef  TYPE_2__ sli4_cmd_read_nvparms_t ;
struct TYPE_10__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  TYPE_1__ ocs_hw_get_nvparms_cb_arg_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_get_nvparms_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_hw_get_nvparms_cb_arg_t *cb_arg = arg;
	sli4_cmd_read_nvparms_t* mbox_rsp = (sli4_cmd_read_nvparms_t*) mqe;

	if (cb_arg->cb) {
		cb_arg->cb(status, mbox_rsp->wwpn, mbox_rsp->wwnn, mbox_rsp->hard_alpa,
				mbox_rsp->preferred_d_id, cb_arg->arg);
	}

	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);
	ocs_free(hw->os, cb_arg, sizeof(ocs_hw_get_nvparms_cb_arg_t));

	return 0;
}