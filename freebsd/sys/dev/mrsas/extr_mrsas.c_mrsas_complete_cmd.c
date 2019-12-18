#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int low; int high; } ;
union desc_value {int /*<<< orphan*/  word; TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct mrsas_softc {scalar_t__ adprecovery; int reply_alloc_sz; int* last_reply_idx; int reply_q_depth; int /*<<< orphan*/ * msix_reg_offset; scalar_t__ msix_combined; scalar_t__ msix_enable; TYPE_11__* reply_desc_mem; struct mrsas_mfi_cmd** mfi_cmd_list; int /*<<< orphan*/  fw_outstanding; TYPE_10__* load_balance_info; int /*<<< orphan*/  ocr_chan; int /*<<< orphan*/  mrsas_dev; struct mrsas_mpt_cmd** mpt_cmd_list; } ;
struct mrsas_mpt_cmd {int* sense; size_t pd_r1_lb; int cmd_completed; int callout_owner; size_t sync_cmd_idx; TYPE_16__* ccb_ptr; int /*<<< orphan*/  cm_callout; TYPE_9__* io_request; struct mrsas_mpt_cmd* peer_cmd; int /*<<< orphan*/  r1_alt_dev_handle; int /*<<< orphan*/  load_balance; } ;
struct mrsas_mfi_cmd {TYPE_2__* frame; } ;
struct TYPE_30__ {int status; int exStatus; } ;
struct TYPE_31__ {TYPE_7__ raid_context; } ;
struct TYPE_32__ {int DataLength; TYPE_8__ RaidContext; } ;
struct TYPE_29__ {int target_id; } ;
struct TYPE_27__ {int status; int exStatus; } ;
struct TYPE_28__ {TYPE_4__ raid_context; } ;
struct TYPE_24__ {int flags; } ;
struct TYPE_25__ {TYPE_1__ hdr; } ;
struct TYPE_23__ {TYPE_6__ ccb_h; } ;
struct TYPE_22__ {int ReplyFlags; int SMID; } ;
struct TYPE_21__ {int /*<<< orphan*/  TaskMID; int /*<<< orphan*/  TaskType; } ;
struct TYPE_20__ {int DataLength; int Function; TYPE_5__ RaidContext; } ;
struct TYPE_19__ {int /*<<< orphan*/  TmRequest; } ;
struct TYPE_18__ {int /*<<< orphan*/  Words; } ;
struct TYPE_17__ {int /*<<< orphan*/ * scsi_pending_cmds; } ;
typedef  TYPE_10__* PLD_LOAD_BALANCE_INFO ;
typedef  TYPE_11__ Mpi2ReplyDescriptorsUnion_t ;
typedef  TYPE_12__ MR_TASK_MANAGE_REQUEST ;
typedef  TYPE_13__ MRSAS_RAID_SCSI_IO_REQUEST ;
typedef  TYPE_14__ MPI2_SCSI_TASK_MANAGE_REQUEST ;
typedef  TYPE_15__ MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  MPI2_REPLY_DESCRIPTORS_UNION ;

/* Variables and functions */
 int DONE ; 
 int MFI_FRAME_DONT_POST_IN_REPLY_QUEUE ; 
 int MFI_STAT_OK ; 
#define  MPI2_FUNCTION_SCSI_IO_REQUEST 131 
#define  MPI2_FUNCTION_SCSI_TASK_MGMT 130 
 int MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK ; 
 int MPI2_RPY_DESCRIPT_FLAGS_UNUSED ; 
 scalar_t__ MRSAS_HW_CRITICAL_ERROR ; 
 int /*<<< orphan*/  MRSAS_LOAD_BALANCE_FLAG ; 
#define  MRSAS_MPI2_FUNCTION_LD_IO_REQUEST 129 
#define  MRSAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST 128 
 int /*<<< orphan*/  MR_DEVHANDLE_INVALID ; 
 int THRESHOLD_REPLY_COUNT ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrsas_atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrsas_cmd_done (struct mrsas_softc*,struct mrsas_mpt_cmd*) ; 
 int /*<<< orphan*/  mrsas_complete_mptmfi_passthru (struct mrsas_softc*,struct mrsas_mfi_cmd*,int) ; 
 int /*<<< orphan*/  mrsas_map_mpt_cmd_status (struct mrsas_mpt_cmd*,TYPE_16__*,int,int,int,int*) ; 
 int /*<<< orphan*/  mrsas_reg_set ; 
 int /*<<< orphan*/  mrsas_release_mfi_cmd (struct mrsas_mfi_cmd*) ; 
 int /*<<< orphan*/  mrsas_release_mpt_cmd (struct mrsas_mpt_cmd*) ; 
 int /*<<< orphan*/  mrsas_write_reg (struct mrsas_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_post_host_index ; 
 int /*<<< orphan*/  wakeup_one (void*) ; 

int
mrsas_complete_cmd(struct mrsas_softc *sc, u_int32_t MSIxIndex)
{
	Mpi2ReplyDescriptorsUnion_t *desc;
	MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *reply_desc;
	MRSAS_RAID_SCSI_IO_REQUEST *scsi_io_req;
	struct mrsas_mpt_cmd *cmd_mpt, *r1_cmd = NULL;
	struct mrsas_mfi_cmd *cmd_mfi;
	u_int8_t reply_descript_type, *sense;
	u_int16_t smid, num_completed;
	u_int8_t status, extStatus;
	union desc_value desc_val;
	PLD_LOAD_BALANCE_INFO lbinfo;
	u_int32_t device_id, data_length;
	int threshold_reply_count = 0;
#if TM_DEBUG
	MR_TASK_MANAGE_REQUEST *mr_tm_req;
	MPI2_SCSI_TASK_MANAGE_REQUEST *mpi_tm_req;
#endif

	/* If we have a hardware error, not need to continue */
	if (sc->adprecovery == MRSAS_HW_CRITICAL_ERROR)
		return (DONE);

	desc = sc->reply_desc_mem;
	desc += ((MSIxIndex * sc->reply_alloc_sz) / sizeof(MPI2_REPLY_DESCRIPTORS_UNION))
	    + sc->last_reply_idx[MSIxIndex];

	reply_desc = (MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *) desc;

	desc_val.word = desc->Words;
	num_completed = 0;

	reply_descript_type = reply_desc->ReplyFlags & MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;

	/* Find our reply descriptor for the command and process */
	while ((desc_val.u.low != 0xFFFFFFFF) && (desc_val.u.high != 0xFFFFFFFF)) {
		smid = reply_desc->SMID;
		cmd_mpt = sc->mpt_cmd_list[smid - 1];
		scsi_io_req = (MRSAS_RAID_SCSI_IO_REQUEST *) cmd_mpt->io_request;

		status = scsi_io_req->RaidContext.raid_context.status;
		extStatus = scsi_io_req->RaidContext.raid_context.exStatus;
		sense = cmd_mpt->sense;
		data_length = scsi_io_req->DataLength;

		switch (scsi_io_req->Function) {
		case MPI2_FUNCTION_SCSI_TASK_MGMT:
#if TM_DEBUG
			mr_tm_req = (MR_TASK_MANAGE_REQUEST *) cmd_mpt->io_request;
			mpi_tm_req = (MPI2_SCSI_TASK_MANAGE_REQUEST *)
			    &mr_tm_req->TmRequest;
			device_printf(sc->mrsas_dev, "TM completion type 0x%X, "
			    "TaskMID: 0x%X", mpi_tm_req->TaskType, mpi_tm_req->TaskMID);
#endif
            wakeup_one((void *)&sc->ocr_chan);
            break;
		case MPI2_FUNCTION_SCSI_IO_REQUEST:	/* Fast Path IO. */
			device_id = cmd_mpt->ccb_ptr->ccb_h.target_id;
			lbinfo = &sc->load_balance_info[device_id];
			/* R1 load balancing for READ */
			if (cmd_mpt->load_balance == MRSAS_LOAD_BALANCE_FLAG) {
				mrsas_atomic_dec(&lbinfo->scsi_pending_cmds[cmd_mpt->pd_r1_lb]);
				cmd_mpt->load_balance &= ~MRSAS_LOAD_BALANCE_FLAG;
			}
			/* Fall thru and complete IO */
		case MRSAS_MPI2_FUNCTION_LD_IO_REQUEST:
			if (cmd_mpt->r1_alt_dev_handle == MR_DEVHANDLE_INVALID) {
				mrsas_map_mpt_cmd_status(cmd_mpt, cmd_mpt->ccb_ptr, status,
				    extStatus, data_length, sense);
				mrsas_cmd_done(sc, cmd_mpt);
				mrsas_atomic_dec(&sc->fw_outstanding);
			} else {
				/*
				 * If the peer  Raid  1/10 fast path failed,
				 * mark IO as failed to the scsi layer.
				 * Overwrite the current status by the failed status
				 * and make sure that if any command fails,
				 * driver returns fail status to CAM.
				 */
				cmd_mpt->cmd_completed = 1;
				r1_cmd = cmd_mpt->peer_cmd;
				if (r1_cmd->cmd_completed) {
					if (r1_cmd->io_request->RaidContext.raid_context.status != MFI_STAT_OK) {
						status = r1_cmd->io_request->RaidContext.raid_context.status;
						extStatus = r1_cmd->io_request->RaidContext.raid_context.exStatus;
						data_length = r1_cmd->io_request->DataLength;
						sense = r1_cmd->sense;
					}
					r1_cmd->ccb_ptr = NULL;
					if (r1_cmd->callout_owner) {
						callout_stop(&r1_cmd->cm_callout);
						r1_cmd->callout_owner  = false;
					}
					mrsas_release_mpt_cmd(r1_cmd);
					mrsas_atomic_dec(&sc->fw_outstanding);
					mrsas_map_mpt_cmd_status(cmd_mpt, cmd_mpt->ccb_ptr, status,
					    extStatus, data_length, sense);
					mrsas_cmd_done(sc, cmd_mpt);
					mrsas_atomic_dec(&sc->fw_outstanding);
				}
			}
			break;
		case MRSAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST:	/* MFI command */
			cmd_mfi = sc->mfi_cmd_list[cmd_mpt->sync_cmd_idx];
			/*
			 * Make sure NOT TO release the mfi command from the called
			 * function's context if it is fired with issue_polled call.
			 * And also make sure that the issue_polled call should only be
			 * used if INTERRUPT IS DISABLED.
			 */
			if (cmd_mfi->frame->hdr.flags & MFI_FRAME_DONT_POST_IN_REPLY_QUEUE)
				mrsas_release_mfi_cmd(cmd_mfi);
			else
				mrsas_complete_mptmfi_passthru(sc, cmd_mfi, status);
			break;
		}

		sc->last_reply_idx[MSIxIndex]++;
		if (sc->last_reply_idx[MSIxIndex] >= sc->reply_q_depth)
			sc->last_reply_idx[MSIxIndex] = 0;

		desc->Words = ~((uint64_t)0x00);	/* set it back to all
							 * 0xFFFFFFFFs */
		num_completed++;
		threshold_reply_count++;

		/* Get the next reply descriptor */
		if (!sc->last_reply_idx[MSIxIndex]) {
			desc = sc->reply_desc_mem;
			desc += ((MSIxIndex * sc->reply_alloc_sz) / sizeof(MPI2_REPLY_DESCRIPTORS_UNION));
		} else
			desc++;

		reply_desc = (MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *) desc;
		desc_val.word = desc->Words;

		reply_descript_type = reply_desc->ReplyFlags & MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;

		if (reply_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED)
			break;

		/*
		 * Write to reply post index after completing threshold reply
		 * count and still there are more replies in reply queue
		 * pending to be completed.
		 */
		if (threshold_reply_count >= THRESHOLD_REPLY_COUNT) {
			if (sc->msix_enable) {
				if (sc->msix_combined)
					mrsas_write_reg(sc, sc->msix_reg_offset[MSIxIndex / 8],
					    ((MSIxIndex & 0x7) << 24) |
					    sc->last_reply_idx[MSIxIndex]);
				else
					mrsas_write_reg(sc, sc->msix_reg_offset[0], (MSIxIndex << 24) |
					    sc->last_reply_idx[MSIxIndex]);
			} else
				mrsas_write_reg(sc, offsetof(mrsas_reg_set,
				    reply_post_host_index), sc->last_reply_idx[0]);

			threshold_reply_count = 0;
		}
	}

	/* No match, just return */
	if (num_completed == 0)
		return (DONE);

	/* Clear response interrupt */
	if (sc->msix_enable) {
		if (sc->msix_combined) {
			mrsas_write_reg(sc, sc->msix_reg_offset[MSIxIndex / 8],
			    ((MSIxIndex & 0x7) << 24) |
			    sc->last_reply_idx[MSIxIndex]);
		} else
			mrsas_write_reg(sc, sc->msix_reg_offset[0], (MSIxIndex << 24) |
			    sc->last_reply_idx[MSIxIndex]);
	} else
		mrsas_write_reg(sc, offsetof(mrsas_reg_set,
		    reply_post_host_index), sc->last_reply_idx[0]);

	return (0);
}