#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {scalar_t__ status; } ;
struct TYPE_11__ {TYPE_1__ hdr; int /*<<< orphan*/ * resp_data; } ;
typedef  TYPE_3__ sli4_cmd_dump4_t ;
typedef  TYPE_2__ ocs_hw_temp_cb_arg_t ;
struct TYPE_12__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_5__ ocs_hw_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_cb_temp(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{

	sli4_cmd_dump4_t* mbox_rsp = (sli4_cmd_dump4_t*) mqe;
	ocs_hw_temp_cb_arg_t *cb_arg = arg;
	uint32_t curr_temp = mbox_rsp->resp_data[0]; /* word 5 */
	uint32_t crit_temp_thrshld = mbox_rsp->resp_data[1]; /* word 6*/
	uint32_t warn_temp_thrshld = mbox_rsp->resp_data[2]; /* word 7 */
	uint32_t norm_temp_thrshld = mbox_rsp->resp_data[3]; /* word 8 */
	uint32_t fan_off_thrshld = mbox_rsp->resp_data[4];   /* word 9 */
	uint32_t fan_on_thrshld = mbox_rsp->resp_data[5];    /* word 10 */

	if (cb_arg) {
		if (cb_arg->cb) {
			if ((status == 0) && mbox_rsp->hdr.status) {
				status = mbox_rsp->hdr.status;
			}
			cb_arg->cb(status,
				   curr_temp,
				   crit_temp_thrshld,
				   warn_temp_thrshld,
				   norm_temp_thrshld,
				   fan_off_thrshld,
				   fan_on_thrshld,
				   cb_arg->arg);
		}

		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_temp_cb_arg_t));
	}
	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);

	return 0;
}