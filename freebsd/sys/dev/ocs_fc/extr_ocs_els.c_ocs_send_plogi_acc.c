#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_16__ {int /*<<< orphan*/  display_name; TYPE_3__* sport; scalar_t__ service_params; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_4__ ocs_node_t ;
struct TYPE_14__ {TYPE_6__* virt; } ;
struct TYPE_13__ {void* ox_id; } ;
struct TYPE_19__ {TYPE_1__ els; } ;
struct TYPE_17__ {char* display_name; int /*<<< orphan*/  hio_type; TYPE_2__ els_req; TYPE_9__ iparam; void* init_task_tag; void* els_callback_arg; int /*<<< orphan*/  els_callback; TYPE_4__* node; } ;
typedef  TYPE_5__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_18__ {int* common_service_parameters; scalar_t__ resv1; int /*<<< orphan*/  command_code; } ;
typedef  TYPE_6__ fc_plogi_payload_t ;
typedef  int /*<<< orphan*/  els_cb_t ;
struct TYPE_15__ {int /*<<< orphan*/  service_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_CMD_ACC ; 
 int /*<<< orphan*/  OCS_HW_ELS_RSP ; 
 int /*<<< orphan*/  node_els_trace () ; 
 int /*<<< orphan*/  ocs_display_sparams (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ocs_els_io_free (TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_els_send_rsp (TYPE_5__*,int) ; 
 int ocs_htobe32 (unsigned int) ; 
 int /*<<< orphan*/  ocs_memcpy (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 

ocs_io_t *
ocs_send_plogi_acc(ocs_io_t *io, uint32_t ox_id, els_cb_t cb, void *cbarg)
{
	ocs_node_t *node = io->node;
	int32_t rc;
	ocs_t *ocs = node->ocs;
	fc_plogi_payload_t *plogi;
	fc_plogi_payload_t *req = (fc_plogi_payload_t *)node->service_params;

	node_els_trace();

	io->els_callback = cb;
	io->els_callback_arg = cbarg;
	io->display_name = "plog_acc";
	io->init_task_tag = ox_id;

	ocs_memset(&io->iparam, 0, sizeof(io->iparam));
	io->iparam.els.ox_id = ox_id;

	plogi = io->els_req.virt;

	/* copy our port's service parameters to payload */
	ocs_memcpy(plogi, node->sport->service_params, sizeof(*plogi));
	plogi->command_code = FC_ELS_CMD_ACC;
	plogi->resv1 = 0;
	
	/* Set Application header support bit if requested */
	if (req->common_service_parameters[1] & ocs_htobe32(1U << 24)) {
		plogi->common_service_parameters[1] |= ocs_htobe32(1U << 24);
	}

	/* Priority tagging support. */
	if (req->common_service_parameters[1] & ocs_htobe32(1U << 23)) {
		plogi->common_service_parameters[1] |= ocs_htobe32(1U << 23);
	}

	ocs_display_sparams(node->display_name, "plogi send resp", 0, NULL, plogi->common_service_parameters);

	io->hio_type = OCS_HW_ELS_RSP;
	if ((rc = ocs_els_send_rsp(io, sizeof(*plogi)))) {
		ocs_els_io_free(io);
		io = NULL;
	}
	return io;
}