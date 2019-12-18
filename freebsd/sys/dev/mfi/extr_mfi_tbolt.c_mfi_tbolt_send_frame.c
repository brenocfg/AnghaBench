#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union mfi_mpi2_request_descriptor {int words; } ;
typedef  int uint8_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_dev; scalar_t__ adpreset; } ;
struct mfi_frame_header {scalar_t__ cmd_status; scalar_t__ cmd; int /*<<< orphan*/  flags; } ;
struct mfi_command {int cm_flags; TYPE_3__* cm_frame; int /*<<< orphan*/  cm_timestamp; } ;
struct TYPE_5__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {int* cdb; } ;
struct TYPE_6__ {TYPE_2__ dcmd; TYPE_1__ pass; struct mfi_frame_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 scalar_t__ MFI_CMD_LD_READ ; 
 scalar_t__ MFI_CMD_LD_SCSI_IO ; 
 scalar_t__ MFI_CMD_LD_WRITE ; 
 scalar_t__ MFI_CMD_PD_SCSI_IO ; 
 int MFI_CMD_POLLED ; 
 int MFI_CMD_SCSI ; 
 int /*<<< orphan*/  MFI_FRAME_DONT_POST_IN_REPLY_QUEUE ; 
 int /*<<< orphan*/  MFI_IHQP ; 
 int /*<<< orphan*/  MFI_ILQP ; 
 scalar_t__ MFI_STAT_INVALID_STATUS ; 
 int /*<<< orphan*/  MFI_WRITE4 (struct mfi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 union mfi_mpi2_request_descriptor* mfi_build_and_issue_cmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_enqueue_busy (struct mfi_command*) ; 
 int mfi_polled_cmd_timeout ; 
 union mfi_mpi2_request_descriptor* mfi_tbolt_build_mpt_cmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_tbolt_complete_cmd (struct mfi_softc*) ; 
 int /*<<< orphan*/  time_uptime ; 

int
mfi_tbolt_send_frame(struct mfi_softc *sc, struct mfi_command *cm)
{
	struct mfi_frame_header *hdr;
	uint8_t *cdb;
	union mfi_mpi2_request_descriptor *req_desc = NULL;
	int tm = mfi_polled_cmd_timeout * 1000;

	hdr = &cm->cm_frame->header;
	cdb = cm->cm_frame->pass.cdb;
	if (sc->adpreset)
		return 1;
	if ((cm->cm_flags & MFI_CMD_POLLED) == 0) {
		cm->cm_timestamp = time_uptime;
		mfi_enqueue_busy(cm);
	} else {	/* still get interrupts for it */
		hdr->cmd_status = MFI_STAT_INVALID_STATUS;
		hdr->flags |= MFI_FRAME_DONT_POST_IN_REPLY_QUEUE;
	}

	if (hdr->cmd == MFI_CMD_PD_SCSI_IO) {
		/* check for inquiry commands coming from CLI */
		if (cdb[0] != 0x28 || cdb[0] != 0x2A) {
			if ((req_desc = mfi_tbolt_build_mpt_cmd(sc, cm)) ==
			    NULL) {
				device_printf(sc->mfi_dev, "Mapping from MFI "
				    "to MPT Failed \n");
				return 1;
			}
		}
		else
			device_printf(sc->mfi_dev, "DJA NA XXX SYSPDIO\n");
	} else if (hdr->cmd == MFI_CMD_LD_SCSI_IO ||
	    hdr->cmd == MFI_CMD_LD_READ || hdr->cmd == MFI_CMD_LD_WRITE) {
		cm->cm_flags |= MFI_CMD_SCSI;
		if ((req_desc = mfi_build_and_issue_cmd(sc, cm)) == NULL) {
			device_printf(sc->mfi_dev, "LDIO Failed \n");
			return 1;
		}
	} else if ((req_desc = mfi_tbolt_build_mpt_cmd(sc, cm)) == NULL) {
		device_printf(sc->mfi_dev, "Mapping from MFI to MPT Failed\n");
		return (1);
	}

	if (cm->cm_flags & MFI_CMD_SCSI) {
		/*
		 * LD IO needs to be posted since it doesn't get
		 * acknowledged via a status update so have the
		 * controller reply via mfi_tbolt_complete_cmd.
		 */
		hdr->flags &= ~MFI_FRAME_DONT_POST_IN_REPLY_QUEUE;
	}

	MFI_WRITE4(sc, MFI_ILQP, (req_desc->words & 0xFFFFFFFF));
	MFI_WRITE4(sc, MFI_IHQP, (req_desc->words >>0x20));

	if ((cm->cm_flags & MFI_CMD_POLLED) == 0)
		return 0;

	/*
	 * This is a polled command, so busy-wait for it to complete.
	 *
	 * The value of hdr->cmd_status is updated directly by the hardware
	 * so there is no guarantee that mfi_tbolt_complete_cmd is called
	 * prior to this value changing.
	 */
	while (hdr->cmd_status == MFI_STAT_INVALID_STATUS) {
		DELAY(1000);
		tm -= 1;
		if (tm <= 0)
			break;
		if (cm->cm_flags & MFI_CMD_SCSI) {
			/*
			 * Force check reply queue.
			 * This ensures that dump works correctly
			 */
			mfi_tbolt_complete_cmd(sc);
		}
	}

	/* ensure the command cleanup has been processed before returning */
	mfi_tbolt_complete_cmd(sc);

	if (hdr->cmd_status == MFI_STAT_INVALID_STATUS) {
		device_printf(sc->mfi_dev, "Frame %p timed out "
		    "command 0x%X\n", hdr, cm->cm_frame->dcmd.opcode);
		return (ETIMEDOUT);
	}
	return 0;
}