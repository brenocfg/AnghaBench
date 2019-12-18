#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_session {size_t is_max_send_data_segment_length; } ;
struct iscsi_outstanding {scalar_t__ io_datasn; TYPE_1__* io_ccb; } ;
struct iscsi_bhs_r2t {int /*<<< orphan*/  bhsr2t_target_transfer_tag; int /*<<< orphan*/  bhsr2t_initiator_task_tag; int /*<<< orphan*/  bhsr2t_lun; int /*<<< orphan*/  bhsr2t_desired_data_transfer_length; int /*<<< orphan*/  bhsr2t_buffer_offset; } ;
struct iscsi_bhs_data_out {int /*<<< orphan*/  bhsdo_flags; void* bhsdo_buffer_offset; void* bhsdo_datasn; int /*<<< orphan*/  bhsdo_target_transfer_tag; int /*<<< orphan*/  bhsdo_initiator_task_tag; int /*<<< orphan*/  bhsdo_lun; int /*<<< orphan*/  bhsdo_opcode; } ;
struct icl_pdu {scalar_t__ ip_bhs; int /*<<< orphan*/  ip_conn; } ;
struct TYPE_4__ {int flags; } ;
struct ccb_scsiio {size_t dxfer_len; scalar_t__ data_ptr; TYPE_2__ ccb_h; } ;
struct TYPE_3__ {struct ccb_scsiio csio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHSDO_FLAGS_F ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_OUT ; 
 int /*<<< orphan*/  ISCSI_BHS_OPCODE_SCSI_DATA_OUT ; 
 int /*<<< orphan*/  ISCSI_SESSION_WARN (struct iscsi_session*,char*,...) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct iscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 void* htonl (size_t) ; 
 int icl_pdu_append_data (struct icl_pdu*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 
 struct icl_pdu* icl_pdu_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_outstanding* iscsi_outstanding_find (struct iscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_pdu_queue_locked (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_session_reconnect (struct iscsi_session*) ; 
 size_t ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iscsi_pdu_handle_r2t(struct icl_pdu *response)
{
	struct icl_pdu *request;
	struct iscsi_session *is;
	struct iscsi_bhs_r2t *bhsr2t;
	struct iscsi_bhs_data_out *bhsdo;
	struct iscsi_outstanding *io;
	struct ccb_scsiio *csio;
	size_t off, len, total_len;
	int error;

	is = PDU_SESSION(response);

	bhsr2t = (struct iscsi_bhs_r2t *)response->ip_bhs;
	io = iscsi_outstanding_find(is, bhsr2t->bhsr2t_initiator_task_tag);
	if (io == NULL || io->io_ccb == NULL) {
		ISCSI_SESSION_WARN(is, "bad itt 0x%x; reconnecting",
		    bhsr2t->bhsr2t_initiator_task_tag);
		icl_pdu_free(response);
		iscsi_session_reconnect(is);
		return;
	}

	csio = &io->io_ccb->csio;

	if ((csio->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_OUT) {
		ISCSI_SESSION_WARN(is, "received R2T for read command; reconnecting");
		icl_pdu_free(response);
		iscsi_session_reconnect(is);
		return;
	}

	/*
	 * XXX: Verify R2TSN.
	 */

	io->io_datasn = 0;

	off = ntohl(bhsr2t->bhsr2t_buffer_offset);
	if (off > csio->dxfer_len) {
		ISCSI_SESSION_WARN(is, "target requested invalid offset "
		    "%zd, buffer is is %d; reconnecting", off, csio->dxfer_len);
		icl_pdu_free(response);
		iscsi_session_reconnect(is);
		return;
	}

	total_len = ntohl(bhsr2t->bhsr2t_desired_data_transfer_length);
	if (total_len == 0 || total_len > csio->dxfer_len) {
		ISCSI_SESSION_WARN(is, "target requested invalid length "
		    "%zd, buffer is %d; reconnecting", total_len, csio->dxfer_len);
		icl_pdu_free(response);
		iscsi_session_reconnect(is);
		return;
	}

	//ISCSI_SESSION_DEBUG(is, "r2t; off %zd, len %zd", off, total_len);

	for (;;) {
		len = total_len;

		if (len > is->is_max_send_data_segment_length)
			len = is->is_max_send_data_segment_length;

		if (off + len > csio->dxfer_len) {
			ISCSI_SESSION_WARN(is, "target requested invalid "
			    "length/offset %zd, buffer is %d; reconnecting",
			    off + len, csio->dxfer_len);
			icl_pdu_free(response);
			iscsi_session_reconnect(is);
			return;
		}

		request = icl_pdu_new(response->ip_conn, M_NOWAIT);
		if (request == NULL) {
			icl_pdu_free(response);
			iscsi_session_reconnect(is);
			return;
		}

		bhsdo = (struct iscsi_bhs_data_out *)request->ip_bhs;
		bhsdo->bhsdo_opcode = ISCSI_BHS_OPCODE_SCSI_DATA_OUT;
		bhsdo->bhsdo_lun = bhsr2t->bhsr2t_lun;
		bhsdo->bhsdo_initiator_task_tag =
		    bhsr2t->bhsr2t_initiator_task_tag;
		bhsdo->bhsdo_target_transfer_tag =
		    bhsr2t->bhsr2t_target_transfer_tag;
		bhsdo->bhsdo_datasn = htonl(io->io_datasn++);
		bhsdo->bhsdo_buffer_offset = htonl(off);
		error = icl_pdu_append_data(request, csio->data_ptr + off, len,
		    M_NOWAIT);
		if (error != 0) {
			ISCSI_SESSION_WARN(is, "failed to allocate memory; "
			    "reconnecting");
			icl_pdu_free(request);
			icl_pdu_free(response);
			iscsi_session_reconnect(is);
			return;
		}

		off += len;
		total_len -= len;

		if (total_len == 0) {
			bhsdo->bhsdo_flags |= BHSDO_FLAGS_F;
			//ISCSI_SESSION_DEBUG(is, "setting F, off %zd", off);
		} else {
			//ISCSI_SESSION_DEBUG(is, "not finished, off %zd", off);
		}

		iscsi_pdu_queue_locked(request);

		if (total_len == 0)
			break;
	}

	icl_pdu_free(response);
}