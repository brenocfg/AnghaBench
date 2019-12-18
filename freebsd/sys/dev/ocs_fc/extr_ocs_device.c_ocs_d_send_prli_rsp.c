#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_12__ {scalar_t__ fc_type; } ;
typedef  TYPE_2__ ocs_t ;
struct TYPE_13__ {scalar_t__ fc_type; void* shutdown_reason; TYPE_1__* sport; } ;
typedef  TYPE_3__ ocs_node_t ;
struct TYPE_14__ {TYPE_3__* node; TYPE_2__* ocs; } ;
typedef  TYPE_4__ ocs_io_t ;
struct TYPE_11__ {scalar_t__ enable_tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_EXPL_NO_ADDITIONAL ; 
 int /*<<< orphan*/  FC_EXPL_REQUEST_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FC_REASON_UNABLE_TO_PERFORM ; 
 void* OCS_NODE_SHUTDOWN_DEFAULT ; 
 int /*<<< orphan*/  __ocs_d_device_ready ; 
 int /*<<< orphan*/  __ocs_d_initiate_shutdown ; 
 int /*<<< orphan*/  node_printf (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  ocs_node_transition (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_scsi_validate_initiator (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_send_ls_rjt (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_send_prli_acc (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ocs_d_send_prli_rsp(ocs_io_t *io, uint16_t ox_id)
{
	ocs_t *ocs = io->ocs;
	ocs_node_t *node = io->node;

	/* If the back-end doesn't support the fc-type, we send an LS_RJT */
	if (ocs->fc_type != node->fc_type) {
		node_printf(node, "PRLI rejected by target-server, fc-type not supported\n");
		ocs_send_ls_rjt(io, ox_id, FC_REASON_UNABLE_TO_PERFORM,
				FC_EXPL_REQUEST_NOT_SUPPORTED, 0, NULL, NULL);
		node->shutdown_reason = OCS_NODE_SHUTDOWN_DEFAULT;
		ocs_node_transition(node, __ocs_d_initiate_shutdown, NULL);
	}

	/* If the back-end doesn't want to talk to this initiator, we send an LS_RJT */
	if (node->sport->enable_tgt && (ocs_scsi_validate_initiator(node) == 0)) {
		node_printf(node, "PRLI rejected by target-server\n");
		ocs_send_ls_rjt(io, ox_id, FC_REASON_UNABLE_TO_PERFORM,
				FC_EXPL_NO_ADDITIONAL, 0, NULL, NULL);
		node->shutdown_reason = OCS_NODE_SHUTDOWN_DEFAULT;
		ocs_node_transition(node, __ocs_d_initiate_shutdown, NULL);
	} else {
		/*sm:  process PRLI payload, send PRLI acc */
		ocs_send_prli_acc(io, ox_id, ocs->fc_type, NULL, NULL);

		/* Immediately go to ready state to avoid window where we're
		 * waiting for the PRLI LS_ACC to complete while holding FCP_CMNDs
		 */
		ocs_node_transition(node, __ocs_d_device_ready, NULL);
	}
}