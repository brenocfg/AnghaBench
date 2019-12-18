#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  eof; int /*<<< orphan*/  actual_read_length; } ;
typedef  TYPE_3__ sli4_res_common_read_object_t ;
struct TYPE_10__ {scalar_t__ status; } ;
struct TYPE_9__ {scalar_t__ embed; } ;
struct TYPE_12__ {TYPE_2__ hdr; TYPE_1__ payload; } ;
typedef  TYPE_4__ sli4_cmd_sli_config_t ;
struct TYPE_13__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_5__ ocs_hw_t ;
struct TYPE_14__ {struct TYPE_14__* mbox_cmd; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_6__ ocs_hw_dump_get_cb_arg_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_cb_dump_get(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{
	sli4_cmd_sli_config_t* mbox_rsp = (sli4_cmd_sli_config_t*) mqe;
	sli4_res_common_read_object_t* rd_obj_rsp = (sli4_res_common_read_object_t*) mbox_rsp->payload.embed;
	ocs_hw_dump_get_cb_arg_t *cb_arg = arg;
	uint32_t bytes_read;
	uint8_t eof;

	bytes_read = rd_obj_rsp->actual_read_length;
	eof = rd_obj_rsp->eof;

	if (cb_arg) {
		if (cb_arg->cb) {
			if ((status == 0) && mbox_rsp->hdr.status) {
				status = mbox_rsp->hdr.status;
			}
			cb_arg->cb(status, bytes_read, eof, cb_arg->arg);
		}

		ocs_free(hw->os, cb_arg->mbox_cmd, SLI4_BMBX_SIZE);
		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_dump_get_cb_arg_t));
	}

	return 0;
}