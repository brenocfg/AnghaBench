#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int status; scalar_t__ opts; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (TYPE_8__*,int,scalar_t__,int /*<<< orphan*/ ) ;TYPE_4__* dma_resp; } ;
typedef  TYPE_5__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  stat_str ;
struct TYPE_16__ {int /*<<< orphan*/  additional_status; int /*<<< orphan*/  status; } ;
struct TYPE_20__ {int clp_status; scalar_t__ resp_length; int /*<<< orphan*/  clp_detailed_status; TYPE_2__ hdr; } ;
typedef  TYPE_6__ sli4_res_dmtf_exec_clp_cmd_t ;
struct TYPE_17__ {int status; } ;
struct TYPE_15__ {scalar_t__ embed; } ;
struct TYPE_21__ {TYPE_3__ hdr; TYPE_1__ payload; } ;
typedef  TYPE_7__ sli4_cmd_sli_config_t ;
struct TYPE_22__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_8__ ocs_hw_t ;
typedef  TYPE_5__ ocs_hw_clp_cb_arg_t ;
typedef  int int32_t ;
struct TYPE_18__ {scalar_t__ size; int /*<<< orphan*/  virt; } ;

/* Variables and functions */
 scalar_t__ OCS_CMD_POLL ; 
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int ocs_hw_clp_resp_get_value (TYPE_8__*,char*,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ocs_strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_hw_dmtf_clp_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{
	int32_t cb_status = 0;
	sli4_cmd_sli_config_t* mbox_rsp = (sli4_cmd_sli_config_t*) mqe;
	sli4_res_dmtf_exec_clp_cmd_t *clp_rsp = (sli4_res_dmtf_exec_clp_cmd_t *) mbox_rsp->payload.embed;
	ocs_hw_clp_cb_arg_t *cb_arg = arg;
	uint32_t result_len = 0;
	int32_t stat_len;
	char stat_str[8];

	/* there are several status codes here, check them all and condense
	 * into a single callback status
	 */
	if (status || mbox_rsp->hdr.status || clp_rsp->clp_status) {
		ocs_log_debug(hw->os, "status=x%x/x%x/x%x  addl=x%x clp=x%x detail=x%x\n",
			status,
			mbox_rsp->hdr.status,
			clp_rsp->hdr.status,
			clp_rsp->hdr.additional_status,
			clp_rsp->clp_status,
			clp_rsp->clp_detailed_status);
		if (status) {
			cb_status = status;
		} else if (mbox_rsp->hdr.status) {
			cb_status = mbox_rsp->hdr.status;
		} else {
			cb_status = clp_rsp->clp_status;
		}
	} else {
		result_len = clp_rsp->resp_length;
	}

	if (cb_status) {
		goto ocs_hw_cb_dmtf_clp_done;
	}

	if ((result_len == 0) || (cb_arg->dma_resp->size < result_len)) {
		ocs_log_test(hw->os, "Invalid response length: resp_len=%zu result len=%d\n",
			     cb_arg->dma_resp->size, result_len);
		cb_status = -1;
		goto ocs_hw_cb_dmtf_clp_done;
	}

	/* parse CLP response to get status */
	stat_len = ocs_hw_clp_resp_get_value(hw, "status", stat_str,
					      sizeof(stat_str),
					      cb_arg->dma_resp->virt,
					      result_len);

	if (stat_len <= 0) {
		ocs_log_test(hw->os, "failed to get status %d\n", stat_len);
		cb_status = -1;
		goto ocs_hw_cb_dmtf_clp_done;
	}

	if (ocs_strcmp(stat_str, "0") != 0) {
		ocs_log_test(hw->os, "CLP status indicates failure=%s\n", stat_str);
		cb_status = -1;
		goto ocs_hw_cb_dmtf_clp_done;
	}

ocs_hw_cb_dmtf_clp_done:

	/* save status in cb_arg for callers with NULL cb's + polling */
	cb_arg->status = cb_status;
	if (cb_arg->cb) {
		cb_arg->cb(hw, cb_status, result_len, cb_arg->arg);
	}
	/* if polling, caller will free memory */
	if (cb_arg->opts != OCS_CMD_POLL) {
		ocs_free(hw->os, cb_arg, sizeof(*cb_arg));
		ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);
	}
}