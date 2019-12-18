#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_15__ {int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_2__ ocs_node_t ;
struct TYPE_14__ {int /*<<< orphan*/  lun; } ;
struct TYPE_16__ {char* display_name; int /*<<< orphan*/  ref; TYPE_1__ tgt_io; int /*<<< orphan*/  tmf_cmd; void* abort_rx_id; void* init_task_tag; TYPE_2__* node; } ;
typedef  TYPE_3__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_17__ {int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; } ;
typedef  TYPE_4__ fc_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_SCSI_TMF_ABORT_TASK ; 
 int /*<<< orphan*/  node_printf (TYPE_2__*,char*,void*,void*) ; 
 void* ocs_be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_bls_send_acc_hdr (TYPE_3__*,TYPE_4__*) ; 
 TYPE_3__* ocs_io_find_tgt_io (int /*<<< orphan*/ *,TYPE_2__*,void*,void*) ; 
 scalar_t__ ocs_ref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_recv_tmf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_process_abts(ocs_io_t *io, fc_header_t *hdr)
{
	ocs_node_t *node = io->node;
	ocs_t *ocs = node->ocs;
	uint16_t ox_id = ocs_be16toh(hdr->ox_id);
	uint16_t rx_id = ocs_be16toh(hdr->rx_id);
	ocs_io_t *abortio;

	abortio = ocs_io_find_tgt_io(ocs, node, ox_id, rx_id);

	/* If an IO was found, attempt to take a reference on it */
	if (abortio != NULL && (ocs_ref_get_unless_zero(&abortio->ref) != 0)) {

		/* Got a reference on the IO. Hold it until backend is notified below */
		node_printf(node, "Abort request: ox_id [%04x] rx_id [%04x]\n",
			    ox_id, rx_id);

		/*
		 * Save the ox_id for the ABTS as the init_task_tag in our manufactured
		 * TMF IO object
		 */
		io->display_name = "abts";
		io->init_task_tag = ox_id;
		/* don't set tgt_task_tag, don't want to confuse with XRI */

		/*
		 * Save the rx_id from the ABTS as it is needed for the BLS response,
		 * regardless of the IO context's rx_id
		 */
		io->abort_rx_id = rx_id;

		/* Call target server command abort */
		io->tmf_cmd = OCS_SCSI_TMF_ABORT_TASK;
		ocs_scsi_recv_tmf(io, abortio->tgt_io.lun, OCS_SCSI_TMF_ABORT_TASK, abortio, 0);

		/*
		 * Backend will have taken an additional reference on the IO if needed;
		 * done with current reference.
		 */
		ocs_ref_put(&abortio->ref); /* ocs_ref_get(): same function */
	} else {
		/*
		 * Either IO was not found or it has been freed between finding it
		 * and attempting to get the reference,
		 */
		node_printf(node, "Abort request: ox_id [%04x], IO not found (exists=%d)\n",
			    ox_id, (abortio != NULL));

		/* Send a BA_ACC */
		ocs_bls_send_acc_hdr(io, hdr);
	}
	return 0;
}