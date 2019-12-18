#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iser_tx_desc {int /*<<< orphan*/  type; int /*<<< orphan*/  iscsi_header; } ;
struct iser_data_buf {int /*<<< orphan*/  data_len; int /*<<< orphan*/  sg; } ;
struct TYPE_2__ {int /*<<< orphan*/  sig_count; } ;
struct iser_conn {TYPE_1__ ib_conn; } ;
struct iscsi_bhs_scsi_command {int bhssc_flags; int /*<<< orphan*/  bhssc_expected_data_transfer_length; int /*<<< orphan*/  bhssc_initiator_task_tag; } ;
struct icl_iser_pdu {struct iser_data_buf* data; struct ccb_scsiio* csio; struct iser_tx_desc desc; } ;
struct ccb_scsiio {int /*<<< orphan*/  dxfer_len; int /*<<< orphan*/  data_ptr; } ;

/* Variables and functions */
 int BHSSC_FLAGS_R ; 
 int BHSSC_FLAGS_W ; 
 int /*<<< orphan*/  ISCSI_TX_SCSI_COMMAND ; 
 size_t ISER_DIR_IN ; 
 size_t ISER_DIR_OUT ; 
 int /*<<< orphan*/  ISER_ERR (char*,struct iser_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iser_create_send_desc (struct iser_conn*,struct iser_tx_desc*) ; 
 int iser_csio_to_sg (struct ccb_scsiio*,struct iser_data_buf*) ; 
 int iser_post_send (TYPE_1__*,struct iser_tx_desc*,int /*<<< orphan*/ ) ; 
 int iser_prepare_read_cmd (struct icl_iser_pdu*) ; 
 int iser_prepare_write_cmd (struct icl_iser_pdu*) ; 
 int /*<<< orphan*/  iser_signal_comp (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int
iser_send_command(struct iser_conn *iser_conn,
		  struct icl_iser_pdu *iser_pdu)
{
	struct iser_data_buf *data_buf;
	struct iser_tx_desc *tx_desc = &iser_pdu->desc;
	struct iscsi_bhs_scsi_command *hdr = (struct iscsi_bhs_scsi_command *) &(iser_pdu->desc.iscsi_header);
	struct ccb_scsiio *csio = iser_pdu->csio;
	int err = 0;
	u8 sig_count = ++iser_conn->ib_conn.sig_count;

	/* build the tx desc regd header and add it to the tx desc dto */
	tx_desc->type = ISCSI_TX_SCSI_COMMAND;
	iser_create_send_desc(iser_conn, tx_desc);

	if (hdr->bhssc_flags & BHSSC_FLAGS_R) {
		data_buf = &iser_pdu->data[ISER_DIR_IN];
	} else {
		data_buf = &iser_pdu->data[ISER_DIR_OUT];
	}

	data_buf->sg = csio->data_ptr;
	data_buf->data_len = csio->dxfer_len;

	if (likely(csio->dxfer_len)) {
		err = iser_csio_to_sg(csio, data_buf);
		if (unlikely(err))
			goto send_command_error;
	}

	if (hdr->bhssc_flags & BHSSC_FLAGS_R) {
		err = iser_prepare_read_cmd(iser_pdu);
		if (err)
			goto send_command_error;
	} else if (hdr->bhssc_flags & BHSSC_FLAGS_W) {
		err = iser_prepare_write_cmd(iser_pdu);
		if (err)
			goto send_command_error;
	}

	err = iser_post_send(&iser_conn->ib_conn, tx_desc,
			     iser_signal_comp(sig_count));
	if (!err)
		return (0);

send_command_error:
	ISER_ERR("iser_conn %p itt %u len %u err %d", iser_conn,
			hdr->bhssc_initiator_task_tag,
			hdr->bhssc_expected_data_transfer_length,
			err);
	return (err);
}