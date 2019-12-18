#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union mfi_mpi2_reply_descriptor {int /*<<< orphan*/  words; } ;
struct TYPE_6__ {int low; int high; } ;
union desc_value {int /*<<< orphan*/  word; TYPE_1__ u; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct mfi_softc {uintptr_t last_reply_idx; uintptr_t reply_size; int mfi_max_fw_cmds; scalar_t__ reply_frame_pool_align; struct mfi_command* mfi_commands; int /*<<< orphan*/  mfi_dev; struct mfi_cmd_tbolt** mfi_cmd_pool_tbolt; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_mpi2_request_raid_scsi_io {int dummy; } ;
struct mfi_mpi2_reply_header {int ReplyFlags; int SMID; } ;
struct mfi_command {int cm_flags; TYPE_5__* cm_frame; } ;
struct mfi_cmd_tbolt {size_t sync_cmd_idx; struct mfi_mpi2_request_raid_scsi_io* io_request; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd_status; } ;
struct TYPE_7__ {int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  cmd_status; } ;
struct TYPE_8__ {TYPE_2__ header; } ;
struct TYPE_10__ {TYPE_4__ header; TYPE_3__ dcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MFI_CMD_POLLED ; 
 int MFI_CMD_SCSI ; 
 int MFI_ON_MFIQ_BUSY ; 
 int /*<<< orphan*/  MFI_RPI ; 
 int /*<<< orphan*/  MFI_STAT_OK ; 
 int /*<<< orphan*/  MFI_WRITE4 (struct mfi_softc*,int /*<<< orphan*/ ,uintptr_t) ; 
 int MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK ; 
 int MPI2_RPY_DESCRIPT_FLAGS_UNUSED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  map_tbolt_cmd_status (struct mfi_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_complete (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_remove_busy (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mfi_tbolt_complete_cmd(struct mfi_softc *sc)
{
	struct mfi_mpi2_reply_header *desc, *reply_desc;
	struct mfi_command *cmd_mfi;	/* For MFA Cmds */
	struct mfi_cmd_tbolt *cmd_tbolt;
	uint16_t smid;
	uint8_t reply_descript_type;
	struct mfi_mpi2_request_raid_scsi_io  *scsi_io_req;
	uint32_t status, extStatus;
	uint16_t num_completed;
	union desc_value val;
	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	desc = (struct mfi_mpi2_reply_header *)
		((uintptr_t)sc->reply_frame_pool_align
		+ sc->last_reply_idx * sc->reply_size);
	reply_desc = desc;

	if (reply_desc == NULL) {
		device_printf(sc->mfi_dev, "reply desc is NULL!!\n");
		return;
	}

	reply_descript_type = reply_desc->ReplyFlags
	     & MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;
	if (reply_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED)
		return;

	num_completed = 0;
	val.word = ((union mfi_mpi2_reply_descriptor *)desc)->words;

	/* Read Reply descriptor */
	while ((val.u.low != 0xFFFFFFFF) && (val.u.high != 0xFFFFFFFF)) {
		smid = reply_desc->SMID;
		if (smid == 0 || smid > sc->mfi_max_fw_cmds) {
			device_printf(sc->mfi_dev, "smid is %d cannot "
			    "proceed - skipping\n", smid);
			goto next;
		}
		cmd_tbolt = sc->mfi_cmd_pool_tbolt[smid - 1];
		if (cmd_tbolt->sync_cmd_idx == sc->mfi_max_fw_cmds) {
			device_printf(sc->mfi_dev, "cmd_tbolt %p "
			    "has invalid sync_cmd_idx=%d - skipping\n",
			    cmd_tbolt, cmd_tbolt->sync_cmd_idx);
			goto next;
		}
		cmd_mfi = &sc->mfi_commands[cmd_tbolt->sync_cmd_idx];
		scsi_io_req = cmd_tbolt->io_request;

		status = cmd_mfi->cm_frame->dcmd.header.cmd_status;
		extStatus = cmd_mfi->cm_frame->dcmd.header.scsi_status;
		map_tbolt_cmd_status(cmd_mfi, status, extStatus);

		/* mfi_tbolt_return_cmd is handled by mfi complete / return */
		if ((cmd_mfi->cm_flags & MFI_CMD_SCSI) != 0 &&
		    (cmd_mfi->cm_flags & MFI_CMD_POLLED) != 0) {
			/* polled LD/SYSPD IO command */
			/* XXX mark okay for now DJA */
			cmd_mfi->cm_frame->header.cmd_status = MFI_STAT_OK;

		} else {
			/* remove command from busy queue if not polled */
			if ((cmd_mfi->cm_flags & MFI_ON_MFIQ_BUSY) != 0)
				mfi_remove_busy(cmd_mfi);

			/* complete the command */
			mfi_complete(sc, cmd_mfi);
		}

next:
		sc->last_reply_idx++;
		if (sc->last_reply_idx >= sc->mfi_max_fw_cmds) {
			MFI_WRITE4(sc, MFI_RPI, sc->last_reply_idx);
			sc->last_reply_idx = 0;
		}

		/* Set it back to all 0xfff */
		((union mfi_mpi2_reply_descriptor*)desc)->words =
			~((uint64_t)0x00);

		num_completed++;

		/* Get the next reply descriptor */
		desc = (struct mfi_mpi2_reply_header *)
		    ((uintptr_t)sc->reply_frame_pool_align
		    + sc->last_reply_idx * sc->reply_size);
		reply_desc = desc;
		val.word = ((union mfi_mpi2_reply_descriptor*)desc)->words;
		reply_descript_type = reply_desc->ReplyFlags
		    & MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;
		if (reply_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED)
			break;
	}

	if (!num_completed)
		return;

	/* update replyIndex to FW */
	if (sc->last_reply_idx)
		MFI_WRITE4(sc, MFI_RPI, sc->last_reply_idx);

	return;
}