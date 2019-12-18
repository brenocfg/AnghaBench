#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_13__ {int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_3__ ocs_node_t ;
struct TYPE_12__ {TYPE_5__* virt; } ;
struct TYPE_11__ {void* ox_id; } ;
struct TYPE_15__ {void* reason_code_exp; void* reason_code; int /*<<< orphan*/  command_code; TYPE_1__ els; } ;
struct TYPE_14__ {char* display_name; int /*<<< orphan*/  hio_type; TYPE_2__ els_req; TYPE_5__ iparam; void* init_task_tag; void* els_callback_arg; int /*<<< orphan*/  els_callback; TYPE_3__* node; } ;
typedef  TYPE_4__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_5__ fc_ls_rjt_payload_t ;
typedef  int /*<<< orphan*/  els_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_CMD_RJT ; 
 int /*<<< orphan*/  OCS_HW_ELS_RSP ; 
 int /*<<< orphan*/  node_els_trace () ; 
 int /*<<< orphan*/  ocs_els_io_free (TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_els_send_rsp (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

ocs_io_t *
ocs_send_ls_rjt(ocs_io_t *io, uint32_t ox_id, uint32_t reason_code, uint32_t reason_code_expl,
		uint32_t vendor_unique, els_cb_t cb, void *cbarg)
{
	ocs_node_t *node = io->node;
	int32_t rc;
	ocs_t *ocs = node->ocs;
	fc_ls_rjt_payload_t *rjt;

	node_els_trace();

	io->els_callback = cb;
	io->els_callback_arg = cbarg;
	io->display_name = "ls_rjt";
	io->init_task_tag = ox_id;

	ocs_memset(&io->iparam, 0, sizeof(io->iparam));
	io->iparam.els.ox_id = ox_id;

	rjt = io->els_req.virt;
	ocs_memset(rjt, 0, sizeof(*rjt));

	rjt->command_code = FC_ELS_CMD_RJT;
	rjt->reason_code = reason_code;
	rjt->reason_code_exp = reason_code_expl;

	io->hio_type = OCS_HW_ELS_RSP;
	if ((rc = ocs_els_send_rsp(io, sizeof(*rjt)))) {
		ocs_els_io_free(io);
		io = NULL;
	}

	return io;
}