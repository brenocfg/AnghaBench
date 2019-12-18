#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/  dif_oper; int /*<<< orphan*/  dif; } ;
struct TYPE_11__ {int wire_len; int /*<<< orphan*/  scsi_tgt_cb_arg; scalar_t__ auto_resp; int /*<<< orphan*/  (* scsi_tgt_cb ) (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  transferred; struct TYPE_11__* ocs; TYPE_4__ hw_dif; } ;
typedef  TYPE_1__ ocs_t ;
typedef  int /*<<< orphan*/  ocs_scsi_io_status_e ;
typedef  int /*<<< orphan*/  (* ocs_scsi_io_cb_t ) (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  ocs_remote_node_t ;
typedef  TYPE_1__ ocs_io_t ;
typedef  int /*<<< orphan*/  ocs_hw_io_t ;
typedef  TYPE_4__ ocs_hw_dif_info_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_RAW_OUT_RAW ; 
 int OCS_SCSI_IO_CMPL ; 
 int OCS_SCSI_IO_CMPL_RSP_SENT ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_ABORTED ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_DIF_APP_TAG_ERROR ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_DIF_GUARD_ERROR ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_DIF_REF_TAG_ERROR ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_ERROR ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_GOOD ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_NEXUS_LOST ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_NO_IO ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  OCS_SCSI_STATUS_TIMEDOUT_AND_ABORTED ; 
 int /*<<< orphan*/  SLI4_DIF_PASS_THROUGH ; 
 int SLI4_FC_DI_ERROR_AE ; 
 int SLI4_FC_DI_ERROR_EDIR ; 
 int SLI4_FC_DI_ERROR_GE ; 
 int SLI4_FC_DI_ERROR_RE ; 
 int SLI4_FC_DI_ERROR_TDPV ; 
#define  SLI4_FC_LOCAL_REJECT_ABORT_REQUESTED 136 
#define  SLI4_FC_LOCAL_REJECT_INVALID_RELOFFSET 135 
#define  SLI4_FC_LOCAL_REJECT_INVALID_RPI 134 
#define  SLI4_FC_LOCAL_REJECT_NO_XRI 133 
#define  SLI4_FC_WCQE_STATUS_DI_ERROR 132 
#define  SLI4_FC_WCQE_STATUS_LOCAL_REJECT 131 
#define  SLI4_FC_WCQE_STATUS_SHUTDOWN 130 
#define  SLI4_FC_WCQE_STATUS_SUCCESS 129 
#define  SLI4_FC_WCQE_STATUS_TARGET_WQE_TIMEOUT 128 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_scsi_check_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_scsi_dif_check_unknown (TYPE_1__*,int,int,int) ; 
 int ocs_scsi_dif_guard_is_crc (int,TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_scsi_io_free_ovfl (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_io_trace (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ocs_target_io_cb(ocs_hw_io_t *hio, ocs_remote_node_t *rnode, uint32_t length,
	int32_t status, uint32_t ext_status, void *app)
{
	ocs_io_t *io = app;
	ocs_t *ocs;
	ocs_scsi_io_status_e scsi_status = OCS_SCSI_STATUS_GOOD;
	uint16_t additional_length;
	uint8_t edir;
	uint8_t tdpv;
	ocs_hw_dif_info_t *dif_info = &io->hw_dif;
	int is_crc;

	ocs_assert(io);

	scsi_io_trace(io, "status x%x ext_status x%x\n", status, ext_status);

	ocs = io->ocs;
	ocs_assert(ocs);

	ocs_scsi_io_free_ovfl(io);

	io->transferred += length;

	/* Call target server completion */
	if (io->scsi_tgt_cb) {
		ocs_scsi_io_cb_t cb = io->scsi_tgt_cb;
		uint32_t flags = 0;

		/* Clear the callback before invoking the callback */
		io->scsi_tgt_cb = NULL;

		/* if status was good, and auto-good-response was set, then callback
		 * target-server with IO_CMPL_RSP_SENT, otherwise send IO_CMPL
		 */
		if ((status == 0) && (io->auto_resp))
			flags |= OCS_SCSI_IO_CMPL_RSP_SENT;
		else
			flags |= OCS_SCSI_IO_CMPL;

		switch (status) {
		case SLI4_FC_WCQE_STATUS_SUCCESS:
			scsi_status = OCS_SCSI_STATUS_GOOD;
			break;
		case SLI4_FC_WCQE_STATUS_DI_ERROR:
			if (ext_status & SLI4_FC_DI_ERROR_GE) {
				scsi_status = OCS_SCSI_STATUS_DIF_GUARD_ERROR;
			} else if (ext_status & SLI4_FC_DI_ERROR_AE) {
				scsi_status = OCS_SCSI_STATUS_DIF_APP_TAG_ERROR;
			} else if (ext_status & SLI4_FC_DI_ERROR_RE) {
				scsi_status = OCS_SCSI_STATUS_DIF_REF_TAG_ERROR;
			} else {
				additional_length = ((ext_status >> 16) & 0xFFFF);

				/* Capture the EDIR and TDPV bits as 0 or 1 for easier printing. */
				edir = !!(ext_status & SLI4_FC_DI_ERROR_EDIR);
				tdpv = !!(ext_status & SLI4_FC_DI_ERROR_TDPV);

				is_crc = ocs_scsi_dif_guard_is_crc(edir, dif_info);

				if (edir == 0) {
					/* For reads, we have everything in memory.  Start checking from beginning. */
					scsi_status = ocs_scsi_dif_check_unknown(io, 0, io->wire_len, is_crc);
				} else {
					/* For writes, use the additional length to determine where to look for the error.
					 * The additional_length field is set to 0 if it is not supported.
					 * The additional length field is valid if:
					 *    . additional_length is not zero
					 *    . Total Data Placed is valid
					 *    . Error Direction is RX (1)
					 *    . Operation is a pass thru (CRC or CKSUM on IN, and CRC or CHKSUM on OUT) (all pass-thru cases except raw)
					 */
					if ((additional_length != 0) && (tdpv != 0) &&
					    (dif_info->dif == SLI4_DIF_PASS_THROUGH) && (dif_info->dif_oper != OCS_HW_SGE_DIF_OP_IN_RAW_OUT_RAW) ) {
						scsi_status = ocs_scsi_dif_check_unknown(io, length, additional_length, is_crc);
					} else {
						/* If we can't do additional checking, then fall-back to guard error */
						scsi_status = OCS_SCSI_STATUS_DIF_GUARD_ERROR;
					}
				}
			}
			break;
		case SLI4_FC_WCQE_STATUS_LOCAL_REJECT:
			switch (ext_status) {
			case SLI4_FC_LOCAL_REJECT_INVALID_RELOFFSET:
			case SLI4_FC_LOCAL_REJECT_ABORT_REQUESTED:
				scsi_status = OCS_SCSI_STATUS_ABORTED;
				break;
			case SLI4_FC_LOCAL_REJECT_INVALID_RPI:
				scsi_status = OCS_SCSI_STATUS_NEXUS_LOST;
				break;
			case SLI4_FC_LOCAL_REJECT_NO_XRI:
				scsi_status = OCS_SCSI_STATUS_NO_IO;
				break;
			default:
				/* TODO: we have seen 0x0d (TX_DMA_FAILED error) */
				scsi_status = OCS_SCSI_STATUS_ERROR;
				break;
			}
			break;

		case SLI4_FC_WCQE_STATUS_TARGET_WQE_TIMEOUT:
			/* target IO timed out */
			scsi_status = OCS_SCSI_STATUS_TIMEDOUT_AND_ABORTED;
			break;

		case SLI4_FC_WCQE_STATUS_SHUTDOWN:
			/* Target IO cancelled by HW */
			scsi_status = OCS_SCSI_STATUS_SHUTDOWN;
			break;

		default:
			scsi_status = OCS_SCSI_STATUS_ERROR;
			break;
		}

		cb(io, scsi_status, flags, io->scsi_tgt_cb_arg);

	}
	ocs_scsi_check_pending(ocs);
}