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
struct TYPE_16__ {int /*<<< orphan*/  display_name; TYPE_3__* sport; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_4__ ocs_node_t ;
struct TYPE_14__ {TYPE_6__* virt; } ;
struct TYPE_13__ {int /*<<< orphan*/  s_id; void* ox_id; } ;
struct TYPE_19__ {TYPE_1__ els_sid; } ;
struct TYPE_17__ {char* display_name; int /*<<< orphan*/  hio_type; TYPE_2__ els_req; TYPE_4__* node; TYPE_9__ iparam; void* init_task_tag; void* els_callback_arg; int /*<<< orphan*/  els_callback; } ;
typedef  TYPE_5__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_18__ {TYPE_9__* class4_service_parameters; TYPE_9__* class3_service_parameters; TYPE_9__* class2_service_parameters; TYPE_9__* class1_service_parameters; int /*<<< orphan*/ * common_service_parameters; scalar_t__ resv1; int /*<<< orphan*/  command_code; } ;
typedef  TYPE_6__ fc_plogi_payload_t ;
typedef  int /*<<< orphan*/  els_cb_t ;
struct TYPE_15__ {int /*<<< orphan*/  service_params; int /*<<< orphan*/  fc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_CMD_ACC ; 
 int /*<<< orphan*/  OCS_HW_ELS_RSP_SID ; 
 int /*<<< orphan*/  node_els_trace () ; 
 int /*<<< orphan*/  ocs_be32toh (unsigned int) ; 
 int /*<<< orphan*/  ocs_display_sparams (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_els_io_free (TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_els_send_rsp (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ocs_memcpy (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 

ocs_io_t *
ocs_send_flogi_acc(ocs_io_t *io, uint32_t ox_id, uint32_t is_fport, els_cb_t cb, void *cbarg)
{
	ocs_node_t *node = io->node;
	int32_t rc;
	ocs_t *ocs = node->ocs;
	fc_plogi_payload_t *flogi;

	node_els_trace();

	io->els_callback = cb;
	io->els_callback_arg = cbarg;
	io->display_name = "flogi_acc";
	io->init_task_tag = ox_id;

	ocs_memset(&io->iparam, 0, sizeof(io->iparam));
	io->iparam.els_sid.ox_id = ox_id;
	io->iparam.els_sid.s_id = io->node->sport->fc_id;

	flogi = io->els_req.virt;

	/* copy our port's service parameters to payload */
	ocs_memcpy(flogi, node->sport->service_params, sizeof(*flogi));

	/* Set F_port */
	if (is_fport) {
		/* Set F_PORT and Multiple N_PORT_ID Assignment */
		flogi->common_service_parameters[1] |= ocs_be32toh(3U << 28);
	}

	flogi->command_code = FC_ELS_CMD_ACC;
	flogi->resv1 = 0;

	ocs_display_sparams(node->display_name, "flogi send resp", 0, NULL, flogi->common_service_parameters);

	ocs_memset(flogi->class1_service_parameters, 0, sizeof(flogi->class1_service_parameters));
	ocs_memset(flogi->class2_service_parameters, 0, sizeof(flogi->class1_service_parameters));
	ocs_memset(flogi->class3_service_parameters, 0, sizeof(flogi->class1_service_parameters));
	ocs_memset(flogi->class4_service_parameters, 0, sizeof(flogi->class1_service_parameters));

	io->hio_type = OCS_HW_ELS_RSP_SID;
	if ((rc = ocs_els_send_rsp(io, sizeof(*flogi)))) {
		ocs_els_io_free(io);
		io = NULL;
	}

	return io;
}