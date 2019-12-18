#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_27__ {int /*<<< orphan*/  io_alloc_failed_count; } ;
typedef  TYPE_3__ ocs_xport_t ;
struct TYPE_28__ {int /*<<< orphan*/  hw; TYPE_3__* xport; } ;
typedef  TYPE_4__ ocs_t ;
struct TYPE_29__ {int /*<<< orphan*/  abort_cnt; TYPE_4__* ocs; } ;
typedef  TYPE_5__ ocs_node_t ;
struct TYPE_30__ {TYPE_11__* io; int /*<<< orphan*/  payload; TYPE_2__* header; } ;
typedef  TYPE_6__ ocs_node_cb_t ;
struct TYPE_31__ {int /*<<< orphan*/  hw_priv; int /*<<< orphan*/  payload; TYPE_2__* header; } ;
typedef  TYPE_7__ ocs_hw_sequence_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_32__ {int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  d_id; int /*<<< orphan*/  s_id; } ;
typedef  TYPE_8__ fc_header_t ;
typedef  int /*<<< orphan*/  cbdata ;
struct TYPE_25__ {TYPE_8__* virt; } ;
struct TYPE_26__ {TYPE_1__ dma; } ;
struct TYPE_24__ {int seq_init; int /*<<< orphan*/  cmd_tgt; TYPE_5__* node; TYPE_4__* ocs; int /*<<< orphan*/  hw_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_ABTS_RCVD ; 
 int /*<<< orphan*/  OCS_HW_SEND_FRAME_CAPABLE ; 
 int /*<<< orphan*/  OCS_SCSI_IO_ROLE_RESPONDER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fc_be24toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_printf (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_atomic_add_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_be16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_hw_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ocs_hw_sequence_free (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/ * ocs_io_find_tgt_io (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_node_post_event (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_11__* ocs_scsi_io_alloc (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_sframe_send_bls_acc (TYPE_5__*,TYPE_7__*) ; 

int32_t
ocs_node_recv_abts_frame(ocs_node_t *node, ocs_hw_sequence_t *seq)
{
	ocs_t *ocs = node->ocs;
	ocs_xport_t *xport = ocs->xport;
	fc_header_t *hdr = seq->header->dma.virt;
	uint16_t ox_id = ocs_be16toh(hdr->ox_id);
	uint16_t rx_id = ocs_be16toh(hdr->rx_id);
	ocs_node_cb_t cbdata;
	int32_t rc = 0;

	node->abort_cnt++;

	/*
	 * Check to see if the IO we want to abort is active, if it not active,
	 * then we can send the BA_ACC using the send frame option
	 */
	if (ocs_io_find_tgt_io(ocs, node, ox_id, rx_id) == NULL) {
		uint32_t send_frame_capable;

		ocs_log_debug(ocs, "IO not found (ox_id %04x)\n", ox_id);

		/* If we have SEND_FRAME capability, then use it to send BA_ACC */
		rc = ocs_hw_get(&ocs->hw, OCS_HW_SEND_FRAME_CAPABLE, &send_frame_capable);
		if ((rc == 0) && send_frame_capable) {
			rc = ocs_sframe_send_bls_acc(node, seq);
			if (rc) {
				ocs_log_test(ocs, "ocs_bls_acc_send_frame failed\n");
			}
			return rc;
		}
		/* continuing */
	}

	ocs_memset(&cbdata, 0, sizeof(cbdata));
	cbdata.header = seq->header;
	cbdata.payload = seq->payload;

	cbdata.io = ocs_scsi_io_alloc(node, OCS_SCSI_IO_ROLE_RESPONDER);
	if (cbdata.io != NULL) {
		cbdata.io->hw_priv = seq->hw_priv;
		/* If we got this far, SIT=1 */
		cbdata.io->seq_init = 1;

		/* fill out generic fields */
		cbdata.io->ocs = ocs;
		cbdata.io->node = node;
		cbdata.io->cmd_tgt = TRUE;

		ocs_node_post_event(node, OCS_EVT_ABTS_RCVD, &cbdata);
	} else {
		ocs_atomic_add_return(&xport->io_alloc_failed_count, 1);
		node_printf(node, "SCSI IO allocation failed for ABTS received s_id %06x d_id %06x ox_id %04x rx_id %04x\n",
			    fc_be24toh(hdr->s_id), fc_be24toh(hdr->d_id), ocs_be16toh(hdr->ox_id), ocs_be16toh(hdr->rx_id));
	}

	/* ABTS processed, return RX buffer to the chip */
	ocs_hw_sequence_free(&ocs->hw, seq);
	return 0;
}