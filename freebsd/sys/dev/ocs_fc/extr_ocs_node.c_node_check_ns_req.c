#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {scalar_t__ virt; } ;
struct TYPE_13__ {scalar_t__ hio_type; scalar_t__ cmd_rsp_code; int /*<<< orphan*/  display_name; struct TYPE_13__* ocs; struct TYPE_13__* els; TYPE_1__ els_req; struct TYPE_13__* app; } ;
typedef  TYPE_2__ ocs_t ;
typedef  int /*<<< orphan*/  ocs_sm_event_t ;
typedef  TYPE_2__ ocs_sm_ctx_t ;
typedef  TYPE_2__ ocs_node_t ;
typedef  int /*<<< orphan*/  (* ocs_node_common_func_t ) (char const*,TYPE_2__*,int /*<<< orphan*/ ,void*) ;
typedef  TYPE_2__ ocs_node_cb_t ;
typedef  int int32_t ;
typedef  TYPE_2__ fcct_iu_header_t ;

/* Variables and functions */
 scalar_t__ OCS_HW_FC_CT ; 
 int /*<<< orphan*/  ocs_assert (TYPE_2__*,int) ; 
 scalar_t__ ocs_htobe16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_2__*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__) ; 

int32_t
node_check_ns_req(ocs_sm_ctx_t *ctx, ocs_sm_event_t evt, void *arg, uint32_t cmd, ocs_node_common_func_t node_common_func, const char *funcname)
{
	ocs_node_t *node = NULL;
	ocs_t *ocs = NULL;
	ocs_node_cb_t *cbdata = arg;
	fcct_iu_header_t *fcct = NULL;
	ocs_assert(ctx, -1);
	node = ctx->app;
	ocs_assert(node, -1);
	ocs = node->ocs;
	ocs_assert(ocs, -1);
	cbdata = arg;
	ocs_assert(cbdata, -1);
	ocs_assert(cbdata->els, -1);
	fcct = (fcct_iu_header_t *)cbdata->els->els_req.virt;
	ocs_assert(fcct, -1);

	if ((cbdata->els->hio_type != OCS_HW_FC_CT) || fcct->cmd_rsp_code != ocs_htobe16(cmd)) {
		if (cbdata->els->hio_type != OCS_HW_FC_CT) {
			ocs_log_debug(node->ocs, "[%s] %-20s expecting NS cmd=x%x received type=%d\n",
				node->display_name, funcname, cmd, cbdata->els->hio_type);
		} else {
			ocs_log_debug(node->ocs, "[%s] %-20s expecting NS cmd=x%x received cmd=x%x\n",
				node->display_name, funcname, cmd, fcct->cmd_rsp_code);
		}
		/* send event to common handler */
		node_common_func(funcname, ctx, evt, arg);
		return -1;
	}
	return 0;
}