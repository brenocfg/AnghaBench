#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int status; int /*<<< orphan*/  path; } ;
struct TYPE_14__ {size_t target_id; int flags; } ;
struct TYPE_10__ {scalar_t__* cdb_bytes; scalar_t__* cdb_ptr; } ;
struct ccb_scsiio {int resid; int sense_len; int* data_ptr; TYPE_5__ ccb_h; int /*<<< orphan*/  sense_data; int /*<<< orphan*/  sense_resid; int /*<<< orphan*/  scsi_status; TYPE_1__ cdb_io; } ;
union ccb {TYPE_6__ ccb_h; struct ccb_scsiio csio; } ;
typedef  scalar_t__ u8 ;
typedef  int u16 ;
typedef  size_t target_id_t ;
struct scsi_vpd_supported_page_list {int* list; int /*<<< orphan*/  length; } ;
struct scsi_sense_data {int dummy; } ;
struct mprsas_target {scalar_t__ is_nvme; int /*<<< orphan*/  supports_SSU; } ;
struct mprsas_softc {int flags; struct mprsas_target* targets; int /*<<< orphan*/  sim; } ;
struct mpr_softc {int mpr_flags; TYPE_2__* mapping_table; int /*<<< orphan*/  control_TLR; int /*<<< orphan*/  SSU_refcount; scalar_t__ SSU_started; int /*<<< orphan*/  buffer_dmat; struct mprsas_softc* sassc; int /*<<< orphan*/  mpr_mtx; } ;
struct TYPE_12__ {int /*<<< orphan*/  SMID; } ;
struct TYPE_13__ {TYPE_3__ Default; } ;
struct mpr_command {int cm_flags; scalar_t__ cm_state; int cm_length; TYPE_9__* cm_targ; TYPE_4__ cm_desc; int /*<<< orphan*/  cm_sense; int /*<<< orphan*/ * cm_reply; int /*<<< orphan*/  cm_ccb; int /*<<< orphan*/  cm_dmamap; int /*<<< orphan*/ * cm_data; union ccb* cm_complete_data; int /*<<< orphan*/  cm_callout; } ;
struct TYPE_17__ {int /*<<< orphan*/  devinfo; int /*<<< orphan*/ * tm; int /*<<< orphan*/  timedout_commands; int /*<<< orphan*/  commands; int /*<<< orphan*/  outstanding; int /*<<< orphan*/  completed; } ;
struct TYPE_16__ {int SCSIState; int /*<<< orphan*/  TransferCount; int /*<<< orphan*/  SCSIStatus; int /*<<< orphan*/  IOCLogInfo; int /*<<< orphan*/  IOCStatus; int /*<<< orphan*/  SenseCount; int /*<<< orphan*/  ResponseInfo; } ;
struct TYPE_11__ {scalar_t__ TLR_bits; int device_info; } ;
typedef  TYPE_7__ MPI2_SCSI_IO_REPLY ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 scalar_t__ CAM_AUTOSENSE_FAIL ; 
 int CAM_AUTOSNS_VALID ; 
 int CAM_CDB_POINTER ; 
 scalar_t__ CAM_CMD_TIMEOUT ; 
 int CAM_DATA_MASK ; 
 scalar_t__ CAM_DATA_RUN_ERR ; 
 int CAM_DATA_VADDR ; 
 scalar_t__ CAM_DEV_NOT_THERE ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 scalar_t__ CAM_REQUEUE_REQ ; 
 scalar_t__ CAM_REQ_ABORTED ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_REQ_CMP_ERR ; 
 scalar_t__ CAM_REQ_INPROG ; 
 scalar_t__ CAM_SCSI_BUS_RESET ; 
 scalar_t__ CAM_SCSI_STATUS_ERROR ; 
 int CAM_SIM_QUEUED ; 
 int CAM_STATUS_MASK ; 
 scalar_t__ CAM_UNREC_HBA_ERROR ; 
 scalar_t__ INQUIRY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
#define  MPI2_IOCSTATUS_INTERNAL_ERROR 147 
#define  MPI2_IOCSTATUS_INVALID_FIELD 146 
#define  MPI2_IOCSTATUS_INVALID_FUNCTION 145 
#define  MPI2_IOCSTATUS_INVALID_SGL 144 
#define  MPI2_IOCSTATUS_INVALID_STATE 143 
#define  MPI2_IOCSTATUS_INVALID_VPID 142 
 int MPI2_IOCSTATUS_MASK ; 
#define  MPI2_IOCSTATUS_OP_STATE_NOT_SUPPORTED 141 
#define  MPI2_IOCSTATUS_SCSI_DATA_OVERRUN 140 
#define  MPI2_IOCSTATUS_SCSI_DATA_UNDERRUN 139 
#define  MPI2_IOCSTATUS_SCSI_DEVICE_NOT_THERE 138 
#define  MPI2_IOCSTATUS_SCSI_EXT_TERMINATED 137 
#define  MPI2_IOCSTATUS_SCSI_INVALID_DEVHANDLE 136 
#define  MPI2_IOCSTATUS_SCSI_IOC_TERMINATED 135 
#define  MPI2_IOCSTATUS_SCSI_IO_DATA_ERROR 134 
#define  MPI2_IOCSTATUS_SCSI_PROTOCOL_ERROR 133 
#define  MPI2_IOCSTATUS_SCSI_RECOVERED_ERROR 132 
#define  MPI2_IOCSTATUS_SCSI_RESIDUAL_MISMATCH 131 
#define  MPI2_IOCSTATUS_SCSI_TASK_MGMT_FAILED 130 
#define  MPI2_IOCSTATUS_SCSI_TASK_TERMINATED 129 
#define  MPI2_IOCSTATUS_SUCCESS 128 
 int MPI2_SAS_DEVICE_INFO_END_DEVICE ; 
 int MPI2_SAS_DEVICE_INFO_MASK_DEVICE_TYPE ; 
 int MPI2_SAS_DEVICE_INFO_SATA_DEVICE ; 
 int MPI2_SAS_DEVICE_INFO_SSP_TARGET ; 
 int /*<<< orphan*/  MPI2_SCSIIO_CONTROL_NO_TLR ; 
 int /*<<< orphan*/  MPI2_SCSIIO_CONTROL_TLR_ON ; 
 int MPI2_SCSI_RI_MASK_REASONCODE ; 
 int MPI2_SCSI_STATE_AUTOSENSE_FAILED ; 
 int MPI2_SCSI_STATE_AUTOSENSE_VALID ; 
 int MPI2_SCSI_STATE_NO_SCSI_STATUS ; 
 int MPI2_SCSI_STATE_RESPONSE_INFO_VALID ; 
 int MPI2_SCSI_STATE_TERMINATED ; 
 int /*<<< orphan*/  MPI2_SCSI_STATUS_COMMAND_TERMINATED ; 
 int /*<<< orphan*/  MPI2_SCSI_STATUS_GOOD ; 
 int /*<<< orphan*/  MPI2_SCSI_STATUS_TASK_ABORTED ; 
 int MPRSAS_QUEUE_FROZEN ; 
 int MPR_CM_FLAGS_DATAIN ; 
 int MPR_CM_FLAGS_DATAOUT ; 
 int MPR_CM_FLAGS_ERROR_MASK ; 
 int MPR_CM_FLAGS_ON_RECOVERY ; 
 int MPR_CM_FLAGS_TIMEDOUT ; 
 scalar_t__ MPR_CM_STATE_BUSY ; 
 int MPR_FLAGS_DIAGRESET ; 
 int /*<<< orphan*/  MPR_FUNCTRACE (struct mpr_softc*) ; 
 int /*<<< orphan*/  MPR_INFO ; 
 int /*<<< orphan*/  MPR_RECOVERY ; 
 int MPR_SCSI_RI_INVALID_FRAME ; 
 int /*<<< orphan*/  MPR_TRACE ; 
 int /*<<< orphan*/  MPR_XINFO ; 
 int /*<<< orphan*/  SCSI_STATUS_OK ; 
 scalar_t__ SI_EVPD ; 
 scalar_t__ START_STOP_UNIT ; 
 scalar_t__ SVPD_SUPPORTED_PAGE_LIST ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mpr_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int T_DIRECT ; 
 int T_SEQUENTIAL ; 
 scalar_t__ UNMAP ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_link ; 
 int /*<<< orphan*/  cm_recovery ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mpr_describe_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mpr_free_command (struct mpr_softc*,struct mpr_command*) ; 
 int /*<<< orphan*/  mpr_iocstatus_string ; 
 int /*<<< orphan*/  mpr_print_scsiio_cmd (struct mpr_softc*,struct mpr_command*) ; 
 int /*<<< orphan*/  mpr_sc_failed_io_info (struct mpr_softc*,struct ccb_scsiio*,TYPE_7__*,TYPE_9__*) ; 
 int /*<<< orphan*/  mprsas_complete_nvme_unmap (struct mpr_softc*,struct mpr_command*) ; 
 scalar_t__ mprsas_get_ccbstatus (union ccb*) ; 
 int /*<<< orphan*/  mprsas_log_command (struct mpr_command*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mprsas_set_ccbstatus (union ccb*,scalar_t__) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* scsiio_cdb_ptr (struct ccb_scsiio*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mprsas_scsiio_complete(struct mpr_softc *sc, struct mpr_command *cm)
{
	MPI2_SCSI_IO_REPLY *rep;
	union ccb *ccb;
	struct ccb_scsiio *csio;
	struct mprsas_softc *sassc;
	struct scsi_vpd_supported_page_list *vpd_list = NULL;
	u8 *TLR_bits, TLR_on, *scsi_cdb;
	int dir = 0, i;
	u16 alloc_len;
	struct mprsas_target *target;
	target_id_t target_id;

	MPR_FUNCTRACE(sc);
	mpr_dprint(sc, MPR_TRACE,
	    "cm %p SMID %u ccb %p reply %p outstanding %u\n", cm,
	    cm->cm_desc.Default.SMID, cm->cm_ccb, cm->cm_reply,
	    cm->cm_targ->outstanding);

	callout_stop(&cm->cm_callout);
	mtx_assert(&sc->mpr_mtx, MA_OWNED);

	sassc = sc->sassc;
	ccb = cm->cm_complete_data;
	csio = &ccb->csio;
	target_id = csio->ccb_h.target_id;
	rep = (MPI2_SCSI_IO_REPLY *)cm->cm_reply;
	/*
	 * XXX KDM if the chain allocation fails, does it matter if we do
	 * the sync and unload here?  It is simpler to do it in every case,
	 * assuming it doesn't cause problems.
	 */
	if (cm->cm_data != NULL) {
		if (cm->cm_flags & MPR_CM_FLAGS_DATAIN)
			dir = BUS_DMASYNC_POSTREAD;
		else if (cm->cm_flags & MPR_CM_FLAGS_DATAOUT)
			dir = BUS_DMASYNC_POSTWRITE;
		bus_dmamap_sync(sc->buffer_dmat, cm->cm_dmamap, dir);
		bus_dmamap_unload(sc->buffer_dmat, cm->cm_dmamap);
	}

	cm->cm_targ->completed++;
	cm->cm_targ->outstanding--;
	TAILQ_REMOVE(&cm->cm_targ->commands, cm, cm_link);
	ccb->ccb_h.status &= ~(CAM_STATUS_MASK | CAM_SIM_QUEUED);

	if (cm->cm_flags & MPR_CM_FLAGS_ON_RECOVERY) {
		TAILQ_REMOVE(&cm->cm_targ->timedout_commands, cm, cm_recovery);
		KASSERT(cm->cm_state == MPR_CM_STATE_BUSY,
		    ("Not busy for CM_FLAGS_TIMEDOUT: %d\n", cm->cm_state));
		cm->cm_flags &= ~MPR_CM_FLAGS_ON_RECOVERY;
		if (cm->cm_reply != NULL)
			mprsas_log_command(cm, MPR_RECOVERY,
			    "completed timedout cm %p ccb %p during recovery "
			    "ioc %x scsi %x state %x xfer %u\n", cm, cm->cm_ccb,
			    le16toh(rep->IOCStatus), rep->SCSIStatus,
			    rep->SCSIState, le32toh(rep->TransferCount));
		else
			mprsas_log_command(cm, MPR_RECOVERY,
			    "completed timedout cm %p ccb %p during recovery\n",
			    cm, cm->cm_ccb);
	} else if (cm->cm_targ->tm != NULL) {
		if (cm->cm_reply != NULL)
			mprsas_log_command(cm, MPR_RECOVERY,
			    "completed cm %p ccb %p during recovery "
			    "ioc %x scsi %x state %x xfer %u\n",
			    cm, cm->cm_ccb, le16toh(rep->IOCStatus),
			    rep->SCSIStatus, rep->SCSIState,
			    le32toh(rep->TransferCount));
		else
			mprsas_log_command(cm, MPR_RECOVERY,
			    "completed cm %p ccb %p during recovery\n",
			    cm, cm->cm_ccb);
	} else if ((sc->mpr_flags & MPR_FLAGS_DIAGRESET) != 0) {
		mprsas_log_command(cm, MPR_RECOVERY,
		    "reset completed cm %p ccb %p\n", cm, cm->cm_ccb);
	}

	if ((cm->cm_flags & MPR_CM_FLAGS_ERROR_MASK) != 0) {
		/*
		 * We ran into an error after we tried to map the command,
		 * so we're getting a callback without queueing the command
		 * to the hardware.  So we set the status here, and it will
		 * be retained below.  We'll go through the "fast path",
		 * because there can be no reply when we haven't actually
		 * gone out to the hardware.
		 */
		mprsas_set_ccbstatus(ccb, CAM_REQUEUE_REQ);

		/*
		 * Currently the only error included in the mask is
		 * MPR_CM_FLAGS_CHAIN_FAILED, which means we're out of
		 * chain frames.  We need to freeze the queue until we get
		 * a command that completed without this error, which will
		 * hopefully have some chain frames attached that we can
		 * use.  If we wanted to get smarter about it, we would
		 * only unfreeze the queue in this condition when we're
		 * sure that we're getting some chain frames back.  That's
		 * probably unnecessary.
		 */
		if ((sassc->flags & MPRSAS_QUEUE_FROZEN) == 0) {
			xpt_freeze_simq(sassc->sim, 1);
			sassc->flags |= MPRSAS_QUEUE_FROZEN;
			mpr_dprint(sc, MPR_XINFO, "Error sending command, "
			    "freezing SIM queue\n");
		}
	}

	/*
	 * Point to the SCSI CDB, which is dependent on the CAM_CDB_POINTER
	 * flag, and use it in a few places in the rest of this function for
	 * convenience. Use the macro if available.
	 */
#if __FreeBSD_version >= 1100103
	scsi_cdb = scsiio_cdb_ptr(csio);
#else
	if (csio->ccb_h.flags & CAM_CDB_POINTER)
		scsi_cdb = csio->cdb_io.cdb_ptr;
	else
		scsi_cdb = csio->cdb_io.cdb_bytes;
#endif

	/*
	 * If this is a Start Stop Unit command and it was issued by the driver
	 * during shutdown, decrement the refcount to account for all of the
	 * commands that were sent.  All SSU commands should be completed before
	 * shutdown completes, meaning SSU_refcount will be 0 after SSU_started
	 * is TRUE.
	 */
	if (sc->SSU_started && (scsi_cdb[0] == START_STOP_UNIT)) {
		mpr_dprint(sc, MPR_INFO, "Decrementing SSU count.\n");
		sc->SSU_refcount--;
	}

	/* Take the fast path to completion */
	if (cm->cm_reply == NULL) {
		if (mprsas_get_ccbstatus(ccb) == CAM_REQ_INPROG) {
			if ((sc->mpr_flags & MPR_FLAGS_DIAGRESET) != 0)
				mprsas_set_ccbstatus(ccb, CAM_SCSI_BUS_RESET);
			else {
				mprsas_set_ccbstatus(ccb, CAM_REQ_CMP);
				csio->scsi_status = SCSI_STATUS_OK;
			}
			if (sassc->flags & MPRSAS_QUEUE_FROZEN) {
				ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
				sassc->flags &= ~MPRSAS_QUEUE_FROZEN;
				mpr_dprint(sc, MPR_XINFO,
				    "Unfreezing SIM queue\n");
			}
		} 

		/*
		 * There are two scenarios where the status won't be
		 * CAM_REQ_CMP.  The first is if MPR_CM_FLAGS_ERROR_MASK is
		 * set, the second is in the MPR_FLAGS_DIAGRESET above.
		 */
		if (mprsas_get_ccbstatus(ccb) != CAM_REQ_CMP) {
			/*
			 * Freeze the dev queue so that commands are
			 * executed in the correct order after error
			 * recovery.
			 */
			ccb->ccb_h.status |= CAM_DEV_QFRZN;
			xpt_freeze_devq(ccb->ccb_h.path, /*count*/ 1);
		}
		mpr_free_command(sc, cm);
		xpt_done(ccb);
		return;
	}

	target = &sassc->targets[target_id];
	if (scsi_cdb[0] == UNMAP &&
	    target->is_nvme &&
	    (csio->ccb_h.flags & CAM_DATA_MASK) == CAM_DATA_VADDR) {
		rep->SCSIStatus = mprsas_complete_nvme_unmap(sc, cm);
		csio->scsi_status = rep->SCSIStatus;
	}

	mprsas_log_command(cm, MPR_XINFO,
	    "ioc %x scsi %x state %x xfer %u\n",
	    le16toh(rep->IOCStatus), rep->SCSIStatus, rep->SCSIState,
	    le32toh(rep->TransferCount));

	switch (le16toh(rep->IOCStatus) & MPI2_IOCSTATUS_MASK) {
	case MPI2_IOCSTATUS_SCSI_DATA_UNDERRUN:
		csio->resid = cm->cm_length - le32toh(rep->TransferCount);
		/* FALLTHROUGH */
	case MPI2_IOCSTATUS_SUCCESS:
	case MPI2_IOCSTATUS_SCSI_RECOVERED_ERROR:
		if ((le16toh(rep->IOCStatus) & MPI2_IOCSTATUS_MASK) ==
		    MPI2_IOCSTATUS_SCSI_RECOVERED_ERROR)
			mprsas_log_command(cm, MPR_XINFO, "recovered error\n");

		/* Completion failed at the transport level. */
		if (rep->SCSIState & (MPI2_SCSI_STATE_NO_SCSI_STATUS |
		    MPI2_SCSI_STATE_TERMINATED)) {
			mprsas_set_ccbstatus(ccb, CAM_REQ_CMP_ERR);
			break;
		}

		/* In a modern packetized environment, an autosense failure
		 * implies that there's not much else that can be done to
		 * recover the command.
		 */
		if (rep->SCSIState & MPI2_SCSI_STATE_AUTOSENSE_FAILED) {
			mprsas_set_ccbstatus(ccb, CAM_AUTOSENSE_FAIL);
			break;
		}

		/*
		 * CAM doesn't care about SAS Response Info data, but if this is
		 * the state check if TLR should be done.  If not, clear the
		 * TLR_bits for the target.
		 */
		if ((rep->SCSIState & MPI2_SCSI_STATE_RESPONSE_INFO_VALID) &&
		    ((le32toh(rep->ResponseInfo) & MPI2_SCSI_RI_MASK_REASONCODE)
		    == MPR_SCSI_RI_INVALID_FRAME)) {
			sc->mapping_table[target_id].TLR_bits =
			    (u8)MPI2_SCSIIO_CONTROL_NO_TLR;
		}

		/*
		 * Intentionally override the normal SCSI status reporting
		 * for these two cases.  These are likely to happen in a
		 * multi-initiator environment, and we want to make sure that
		 * CAM retries these commands rather than fail them.
		 */
		if ((rep->SCSIStatus == MPI2_SCSI_STATUS_COMMAND_TERMINATED) ||
		    (rep->SCSIStatus == MPI2_SCSI_STATUS_TASK_ABORTED)) {
			mprsas_set_ccbstatus(ccb, CAM_REQ_ABORTED);
			break;
		}

		/* Handle normal status and sense */
		csio->scsi_status = rep->SCSIStatus;
		if (rep->SCSIStatus == MPI2_SCSI_STATUS_GOOD)
			mprsas_set_ccbstatus(ccb, CAM_REQ_CMP);
		else
			mprsas_set_ccbstatus(ccb, CAM_SCSI_STATUS_ERROR);

		if (rep->SCSIState & MPI2_SCSI_STATE_AUTOSENSE_VALID) {
			int sense_len, returned_sense_len;

			returned_sense_len = min(le32toh(rep->SenseCount),
			    sizeof(struct scsi_sense_data));
			if (returned_sense_len < csio->sense_len)
				csio->sense_resid = csio->sense_len -
				    returned_sense_len;
			else
				csio->sense_resid = 0;

			sense_len = min(returned_sense_len,
			    csio->sense_len - csio->sense_resid);
			bzero(&csio->sense_data, sizeof(csio->sense_data));
			bcopy(cm->cm_sense, &csio->sense_data, sense_len);
			ccb->ccb_h.status |= CAM_AUTOSNS_VALID;
		}

		/*
		 * Check if this is an INQUIRY command.  If it's a VPD inquiry,
		 * and it's page code 0 (Supported Page List), and there is
		 * inquiry data, and this is for a sequential access device, and
		 * the device is an SSP target, and TLR is supported by the
		 * controller, turn the TLR_bits value ON if page 0x90 is
		 * supported.
		 */
		if ((scsi_cdb[0] == INQUIRY) &&
		    (scsi_cdb[1] & SI_EVPD) &&
		    (scsi_cdb[2] == SVPD_SUPPORTED_PAGE_LIST) &&
		    ((csio->ccb_h.flags & CAM_DATA_MASK) == CAM_DATA_VADDR) &&
		    (csio->data_ptr != NULL) &&
		    ((csio->data_ptr[0] & 0x1f) == T_SEQUENTIAL) &&
		    (sc->control_TLR) &&
		    (sc->mapping_table[target_id].device_info &
		    MPI2_SAS_DEVICE_INFO_SSP_TARGET)) {
			vpd_list = (struct scsi_vpd_supported_page_list *)
			    csio->data_ptr;
			TLR_bits = &sc->mapping_table[target_id].TLR_bits;
			*TLR_bits = (u8)MPI2_SCSIIO_CONTROL_NO_TLR;
			TLR_on = (u8)MPI2_SCSIIO_CONTROL_TLR_ON;
			alloc_len = ((u16)scsi_cdb[3] << 8) + scsi_cdb[4];
			alloc_len -= csio->resid;
			for (i = 0; i < MIN(vpd_list->length, alloc_len); i++) {
				if (vpd_list->list[i] == 0x90) {
					*TLR_bits = TLR_on;
					break;
				}
			}
		}

		/*
		 * If this is a SATA direct-access end device, mark it so that
		 * a SCSI StartStopUnit command will be sent to it when the
		 * driver is being shutdown.
		 */
		if ((scsi_cdb[0] == INQUIRY) &&
		    (csio->data_ptr != NULL) &&
		    ((csio->data_ptr[0] & 0x1f) == T_DIRECT) &&
		    (sc->mapping_table[target_id].device_info &
		    MPI2_SAS_DEVICE_INFO_SATA_DEVICE) &&
		    ((sc->mapping_table[target_id].device_info &
		    MPI2_SAS_DEVICE_INFO_MASK_DEVICE_TYPE) ==
		    MPI2_SAS_DEVICE_INFO_END_DEVICE)) {
			target = &sassc->targets[target_id];
			target->supports_SSU = TRUE;
			mpr_dprint(sc, MPR_XINFO, "Target %d supports SSU\n",
			    target_id);
		}
		break;
	case MPI2_IOCSTATUS_SCSI_INVALID_DEVHANDLE:
	case MPI2_IOCSTATUS_SCSI_DEVICE_NOT_THERE:
		/*
		 * If devinfo is 0 this will be a volume.  In that case don't
		 * tell CAM that the volume is not there.  We want volumes to
		 * be enumerated until they are deleted/removed, not just
		 * failed.
		 */
		if (cm->cm_targ->devinfo == 0)
			mprsas_set_ccbstatus(ccb, CAM_REQ_CMP);
		else
			mprsas_set_ccbstatus(ccb, CAM_DEV_NOT_THERE);
		break;
	case MPI2_IOCSTATUS_INVALID_SGL:
		mpr_print_scsiio_cmd(sc, cm);
		mprsas_set_ccbstatus(ccb, CAM_UNREC_HBA_ERROR);
		break;
	case MPI2_IOCSTATUS_SCSI_TASK_TERMINATED:
		/*
		 * This is one of the responses that comes back when an I/O
		 * has been aborted.  If it is because of a timeout that we
		 * initiated, just set the status to CAM_CMD_TIMEOUT.
		 * Otherwise set it to CAM_REQ_ABORTED.  The effect on the
		 * command is the same (it gets retried, subject to the
		 * retry counter), the only difference is what gets printed
		 * on the console.
		 */
		if (cm->cm_flags & MPR_CM_FLAGS_TIMEDOUT)
			mprsas_set_ccbstatus(ccb, CAM_CMD_TIMEOUT);
		else
			mprsas_set_ccbstatus(ccb, CAM_REQ_ABORTED);
		break;
	case MPI2_IOCSTATUS_SCSI_DATA_OVERRUN:
		/* resid is ignored for this condition */
		csio->resid = 0;
		mprsas_set_ccbstatus(ccb, CAM_DATA_RUN_ERR);
		break;
	case MPI2_IOCSTATUS_SCSI_IOC_TERMINATED:
	case MPI2_IOCSTATUS_SCSI_EXT_TERMINATED:
		/*
		 * These can sometimes be transient transport-related
		 * errors, and sometimes persistent drive-related errors.
		 * We used to retry these without decrementing the retry
		 * count by returning CAM_REQUEUE_REQ.  Unfortunately, if
		 * we hit a persistent drive problem that returns one of
		 * these error codes, we would retry indefinitely.  So,
		 * return CAM_REQ_CMP_ERROR so that we decrement the retry
		 * count and avoid infinite retries.  We're taking the
		 * potential risk of flagging false failures in the event
		 * of a topology-related error (e.g. a SAS expander problem
		 * causes a command addressed to a drive to fail), but
		 * avoiding getting into an infinite retry loop.
		 */
		mprsas_set_ccbstatus(ccb, CAM_REQ_CMP_ERR);
		mpr_dprint(sc, MPR_INFO,
		    "Controller reported %s tgt %u SMID %u loginfo %x\n",
		    mpr_describe_table(mpr_iocstatus_string,
		    le16toh(rep->IOCStatus) & MPI2_IOCSTATUS_MASK),
		    target_id, cm->cm_desc.Default.SMID,
		    le32toh(rep->IOCLogInfo));
		mpr_dprint(sc, MPR_XINFO,
		    "SCSIStatus %x SCSIState %x xfercount %u\n",
		    rep->SCSIStatus, rep->SCSIState,
		    le32toh(rep->TransferCount));
		break;
	case MPI2_IOCSTATUS_INVALID_FUNCTION:
	case MPI2_IOCSTATUS_INTERNAL_ERROR:
	case MPI2_IOCSTATUS_INVALID_VPID:
	case MPI2_IOCSTATUS_INVALID_FIELD:
	case MPI2_IOCSTATUS_INVALID_STATE:
	case MPI2_IOCSTATUS_OP_STATE_NOT_SUPPORTED:
	case MPI2_IOCSTATUS_SCSI_IO_DATA_ERROR:
	case MPI2_IOCSTATUS_SCSI_PROTOCOL_ERROR:
	case MPI2_IOCSTATUS_SCSI_RESIDUAL_MISMATCH:
	case MPI2_IOCSTATUS_SCSI_TASK_MGMT_FAILED:
	default:
		mprsas_log_command(cm, MPR_XINFO,
		    "completed ioc %x loginfo %x scsi %x state %x xfer %u\n",
		    le16toh(rep->IOCStatus), le32toh(rep->IOCLogInfo),
		    rep->SCSIStatus, rep->SCSIState,
		    le32toh(rep->TransferCount));
		csio->resid = cm->cm_length;

		if (scsi_cdb[0] == UNMAP &&
		    target->is_nvme &&
		    (csio->ccb_h.flags & CAM_DATA_MASK) == CAM_DATA_VADDR)
			mprsas_set_ccbstatus(ccb, CAM_REQ_CMP);
		else
			mprsas_set_ccbstatus(ccb, CAM_REQ_CMP_ERR);

		break;
	}
	
	mpr_sc_failed_io_info(sc, csio, rep, cm->cm_targ);

	if (sassc->flags & MPRSAS_QUEUE_FROZEN) {
		ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
		sassc->flags &= ~MPRSAS_QUEUE_FROZEN;
		mpr_dprint(sc, MPR_XINFO, "Command completed, unfreezing SIM "
		    "queue\n");
	}

	if (mprsas_get_ccbstatus(ccb) != CAM_REQ_CMP) {
		ccb->ccb_h.status |= CAM_DEV_QFRZN;
		xpt_freeze_devq(ccb->ccb_h.path, /*count*/ 1);
	}

	mpr_free_command(sc, cm);
	xpt_done(ccb);
}