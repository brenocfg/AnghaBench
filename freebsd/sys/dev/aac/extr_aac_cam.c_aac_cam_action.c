#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_4__* entries; } ;
struct TYPE_12__ {int func_code; int flags; int /*<<< orphan*/  timeout; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; void* status; TYPE_5__ sim_priv; } ;
struct TYPE_19__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct ccb_scsiio {scalar_t__ dxfer_len; scalar_t__ data_ptr; TYPE_6__ cdb_io; int /*<<< orphan*/  cdb_len; } ;
struct ccb_trans_settings_spi {int /*<<< orphan*/  valid; } ;
struct TYPE_15__ {struct ccb_trans_settings_spi spi; } ;
struct ccb_trans_settings_scsi {int /*<<< orphan*/  valid; } ;
struct TYPE_14__ {struct ccb_trans_settings_scsi scsi; } ;
struct TYPE_16__ {int transport_version; void* transport; void* protocol_version; void* protocol; TYPE_2__ xport_specific; TYPE_1__ proto_specific; } ;
struct ccb_pathinq {int version_num; int hba_misc; int max_lun; int base_transfer_speed; int transport_version; void* protocol_version; void* protocol; void* transport; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  max_target; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
struct ccb_calc_geometry {long volume_size; long block_size; int heads; int secs_per_track; int cylinders; } ;
union ccb {TYPE_10__ ccb_h; struct ccb_scsiio csio; TYPE_3__ cts; struct ccb_pathinq cpi; struct ccb_calc_geometry ccg; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct cam_sim {int dummy; } ;
struct TYPE_21__ {int SgCount; TYPE_7__* SgEntry; } ;
struct aac_srb {scalar_t__ retry_limit; int /*<<< orphan*/  timeout; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; int /*<<< orphan*/  function; scalar_t__ data_len; TYPE_8__ sg_map; int /*<<< orphan*/  cdb_len; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  flags; } ;
struct aac_softc {int flags; int /*<<< orphan*/  aac_dev; } ;
struct aac_fib_header {int dummy; } ;
struct TYPE_13__ {int XferState; int Size; void* Command; } ;
struct aac_fib {TYPE_11__ Header; int /*<<< orphan*/ * data; } ;
struct aac_event {int /*<<< orphan*/  ev_type; union ccb* ev_arg; int /*<<< orphan*/  ev_callback; } ;
struct aac_command {int cm_flags; int /*<<< orphan*/  cm_sc; int /*<<< orphan*/  cm_timestamp; union ccb* cm_private; int /*<<< orphan*/  cm_complete; TYPE_8__* cm_sgtable; scalar_t__ cm_datalen; void* cm_data; struct aac_fib* cm_fib; } ;
struct aac_cam {TYPE_9__* inf; } ;
struct TYPE_22__ {int /*<<< orphan*/  BusNumber; int /*<<< orphan*/  InitiatorBusId; int /*<<< orphan*/  TargetsPerBus; struct aac_softc* aac_sc; } ;
struct TYPE_20__ {scalar_t__ SgByteCount; int /*<<< orphan*/  SgAddress; } ;
struct TYPE_17__ {struct aac_cam* ptr; } ;

/* Variables and functions */
 int AAC_CMD_DATAIN ; 
 int AAC_CMD_DATAOUT ; 
 int /*<<< orphan*/  AAC_EVENT_CMFREE ; 
 int AAC_FIBSTATE_FROMHOST ; 
 int AAC_FIBSTATE_HOSTOWNED ; 
 int AAC_FIBSTATE_INITIALISED ; 
 int AAC_FIBSTATE_NORM ; 
 int AAC_FIBSTATE_REXPECTED ; 
 int AAC_FLAGS_CAM_NORESET ; 
 int AAC_FLAGS_SG_64BIT ; 
 int /*<<< orphan*/  AAC_SRB_FLAGS_DATA_IN ; 
 int /*<<< orphan*/  AAC_SRB_FLAGS_DATA_OUT ; 
 int /*<<< orphan*/  AAC_SRB_FLAGS_NO_DATA_XFER ; 
 int /*<<< orphan*/  AAC_SRB_FLAGS_UNSPECIFIED_DIRECTION ; 
 int /*<<< orphan*/  AAC_SRB_FUNC_EXECUTE_SCSI ; 
 int /*<<< orphan*/  AAC_SRB_FUNC_RESET_DEVICE ; 
 int CAM_CDB_POINTER ; 
 int CAM_DATA_MASK ; 
#define  CAM_DATA_PADDR 141 
#define  CAM_DATA_VADDR 140 
#define  CAM_DIR_IN 139 
 int CAM_DIR_MASK ; 
#define  CAM_DIR_NONE 138 
#define  CAM_DIR_OUT 137 
 void* CAM_FUNC_NOTAVAIL ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 void* CAM_PROVIDE_FAIL ; 
 void* CAM_REQ_CMP ; 
 void* CAM_RESRC_UNAVAIL ; 
 int /*<<< orphan*/  CTS_SCSI_VALID_TQ ; 
 int /*<<< orphan*/  CTS_SPI_VALID_DISC ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int /*<<< orphan*/  M_AACCAM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int PIM_NOBUSRESET ; 
 int PIM_SEQSCAN ; 
 int /*<<< orphan*/  PI_WIDE_16 ; 
 void* PROTO_SCSI ; 
 void* SCSI_REV_2 ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 void* ScsiPortCommand ; 
 void* ScsiPortCommandU64 ; 
 void* XPORT_SPI ; 
#define  XPT_ABORT 136 
#define  XPT_CALC_GEOMETRY 135 
#define  XPT_GET_TRAN_SETTINGS 134 
#define  XPT_PATH_INQ 133 
#define  XPT_RESET_BUS 132 
#define  XPT_RESET_DEV 131 
#define  XPT_SCSI_IO 130 
#define  XPT_SET_TRAN_SETTINGS 129 
#define  XPT_TERM_IO 128 
 int /*<<< orphan*/  aac_add_event (struct aac_softc*,struct aac_event*) ; 
 scalar_t__ aac_alloc_command (struct aac_softc*,struct aac_command**) ; 
 void* aac_cam_abort_ccb (struct cam_sim*,union ccb*) ; 
 int /*<<< orphan*/  aac_cam_complete ; 
 int /*<<< orphan*/  aac_cam_event ; 
 void* aac_cam_reset_bus (struct cam_sim*,union ccb*) ; 
 void* aac_cam_term_io (struct cam_sim*,union ccb*) ; 
 int /*<<< orphan*/  aac_enqueue_ready (struct aac_command*) ; 
 int /*<<< orphan*/  aac_startio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 struct aac_event* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_uptime ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (struct cam_sim*,int) ; 

__attribute__((used)) static void
aac_cam_action(struct cam_sim *sim, union ccb *ccb)
{
	struct	aac_cam *camsc;
	struct	aac_softc *sc;
	struct	aac_srb *srb;
	struct	aac_fib *fib;
	struct	aac_command *cm;

	camsc = (struct aac_cam *)cam_sim_softc(sim);
	sc = camsc->inf->aac_sc;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* Synchronous ops, and ops that don't require communication with the
	 * controller */
	switch(ccb->ccb_h.func_code) {
	case XPT_SCSI_IO:
	case XPT_RESET_DEV:
		/* These are handled down below */
		break;
	case XPT_CALC_GEOMETRY:
	{
		struct ccb_calc_geometry *ccg;
		u_int32_t size_mb;
		u_int32_t secs_per_cylinder;

		ccg = &ccb->ccg;
		size_mb = ccg->volume_size /
		    ((1024L * 1024L) / ccg->block_size);
		if (size_mb >= (2 * 1024)) {		/* 2GB */
			ccg->heads = 255;
			ccg->secs_per_track = 63;
		} else if (size_mb >= (1 * 1024)) {	/* 1GB */
			ccg->heads = 128;
			ccg->secs_per_track = 32;
		} else {
			ccg->heads = 64;
			ccg->secs_per_track = 32;
		}
		secs_per_cylinder = ccg->heads * ccg->secs_per_track;
		ccg->cylinders = ccg->volume_size / secs_per_cylinder;

		ccb->ccb_h.status = CAM_REQ_CMP;
		xpt_done(ccb);
		return;
	}
	case XPT_PATH_INQ:
	{
		struct ccb_pathinq *cpi = &ccb->cpi;

		cpi->version_num = 1;
		cpi->hba_inquiry = PI_WIDE_16;
		cpi->target_sprt = 0;

		/*
		 * Resetting via the passthrough or parallel bus scan
		 * causes problems.
		 */
		cpi->hba_misc = PIM_NOBUSRESET | PIM_SEQSCAN;
		cpi->hba_eng_cnt = 0;
		cpi->max_target = camsc->inf->TargetsPerBus;
		cpi->max_lun = 8;	/* Per the controller spec */
		cpi->initiator_id = camsc->inf->InitiatorBusId;
		cpi->bus_id = camsc->inf->BusNumber;
		cpi->base_transfer_speed = 3300;
		strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
		strlcpy(cpi->hba_vid, "Adaptec", HBA_IDLEN);
		strlcpy(cpi->dev_name, cam_sim_name(sim), DEV_IDLEN);
		cpi->unit_number = cam_sim_unit(sim);
		cpi->transport = XPORT_SPI;
		cpi->transport_version = 2;
		cpi->protocol = PROTO_SCSI;
		cpi->protocol_version = SCSI_REV_2;
		ccb->ccb_h.status = CAM_REQ_CMP;
		xpt_done(ccb);
		return;
	}
	case XPT_GET_TRAN_SETTINGS:
	{
		struct ccb_trans_settings_scsi *scsi =
			&ccb->cts.proto_specific.scsi;
		struct ccb_trans_settings_spi *spi =
			&ccb->cts.xport_specific.spi;
		ccb->cts.protocol = PROTO_SCSI;
		ccb->cts.protocol_version = SCSI_REV_2;
		ccb->cts.transport = XPORT_SPI;
		ccb->cts.transport_version = 2;
		if (ccb->ccb_h.target_lun != CAM_LUN_WILDCARD) {
			scsi->valid = CTS_SCSI_VALID_TQ;
			spi->valid |= CTS_SPI_VALID_DISC;
		} else {
			scsi->valid = 0;
		}
		ccb->ccb_h.status = CAM_REQ_CMP;
		xpt_done(ccb);
		return;
	}
	case XPT_SET_TRAN_SETTINGS:
		ccb->ccb_h.status = CAM_FUNC_NOTAVAIL;
		xpt_done(ccb);
		return;
	case XPT_RESET_BUS:
		if (!(sc->flags & AAC_FLAGS_CAM_NORESET)) {
			ccb->ccb_h.status = aac_cam_reset_bus(sim, ccb);
		} else {
			ccb->ccb_h.status = CAM_REQ_CMP;
		}
		xpt_done(ccb);
		return;
	case XPT_ABORT:
		ccb->ccb_h.status = aac_cam_abort_ccb(sim, ccb);
		xpt_done(ccb);
		return;
	case XPT_TERM_IO:
		ccb->ccb_h.status = aac_cam_term_io(sim, ccb);
		xpt_done(ccb);
		return;
	default:
		device_printf(sc->aac_dev, "Unsupported command 0x%x\n",
		    ccb->ccb_h.func_code);
		ccb->ccb_h.status = CAM_PROVIDE_FAIL;
		xpt_done(ccb);
		return;
	}

	/* Async ops that require communcation with the controller */

	if (aac_alloc_command(sc, &cm)) {
		struct aac_event *event;

		xpt_freeze_simq(sim, 1);
		ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
		ccb->ccb_h.sim_priv.entries[0].ptr = camsc;
		event = malloc(sizeof(struct aac_event), M_AACCAM,
		    M_NOWAIT | M_ZERO);
		if (event == NULL) {
			device_printf(sc->aac_dev,
			    "Warning, out of memory for event\n");
			return;
		}
		event->ev_callback = aac_cam_event;
		event->ev_arg = ccb;
		event->ev_type = AAC_EVENT_CMFREE;
		aac_add_event(sc, event);
		return;
	}

	fib = cm->cm_fib;
	srb = (struct aac_srb *)&fib->data[0];
	cm->cm_datalen = 0;

	switch (ccb->ccb_h.flags & CAM_DIR_MASK) {
	case CAM_DIR_IN:
		srb->flags = AAC_SRB_FLAGS_DATA_IN;
		cm->cm_flags |= AAC_CMD_DATAIN;
		break;
	case CAM_DIR_OUT:
		srb->flags = AAC_SRB_FLAGS_DATA_OUT;
		cm->cm_flags |= AAC_CMD_DATAOUT;
		break;
	case CAM_DIR_NONE:
		srb->flags = AAC_SRB_FLAGS_NO_DATA_XFER;
		break;
	default:
		srb->flags = AAC_SRB_FLAGS_UNSPECIFIED_DIRECTION;
		cm->cm_flags |= AAC_CMD_DATAIN | AAC_CMD_DATAOUT;
		break;
	}

	switch(ccb->ccb_h.func_code) {
	case XPT_SCSI_IO:
	{
		struct ccb_scsiio *csio = &ccb->csio;

		srb->function = AAC_SRB_FUNC_EXECUTE_SCSI;

		/*
		 * Copy the CDB into the SRB.  It's only 6-16 bytes,
		 * so a copy is not too expensive.
		 */
		srb->cdb_len = csio->cdb_len;
		if (ccb->ccb_h.flags & CAM_CDB_POINTER)
			bcopy(csio->cdb_io.cdb_ptr, (u_int8_t *)&srb->cdb[0],
			    srb->cdb_len);
		else
			bcopy(csio->cdb_io.cdb_bytes, (u_int8_t *)&srb->cdb[0],
			    srb->cdb_len);

		/* Set command */
		fib->Header.Command = (sc->flags & AAC_FLAGS_SG_64BIT) ?
			ScsiPortCommandU64 : ScsiPortCommand;

		/* Map the s/g list. XXX 32bit addresses only! */
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
			switch ((ccb->ccb_h.flags & CAM_DATA_MASK)) {
			case CAM_DATA_VADDR:
				srb->data_len = csio->dxfer_len;
				/*
				 * Arrange things so that the S/G
				 * map will get set up automagically
				 */
				cm->cm_data = (void *)csio->data_ptr;
				cm->cm_datalen = csio->dxfer_len;
				cm->cm_sgtable = &srb->sg_map;
				break;
			case CAM_DATA_PADDR:
				/* Send a 32bit command */
				fib->Header.Command = ScsiPortCommand;
				srb->sg_map.SgCount = 1;
				srb->sg_map.SgEntry[0].SgAddress =
				    (uint32_t)(uintptr_t)csio->data_ptr;
				srb->sg_map.SgEntry[0].SgByteCount =
				    csio->dxfer_len;
				srb->data_len = csio->dxfer_len;
				break;
			default:
				/* XXX Need to handle multiple s/g elements */
				panic("aac_cam: multiple s/g elements");
			}
		} else {
			srb->sg_map.SgCount = 0;
			srb->sg_map.SgEntry[0].SgByteCount = 0;
			srb->data_len = 0;
		}

		break;
	}
	case XPT_RESET_DEV:
		if (!(sc->flags & AAC_FLAGS_CAM_NORESET)) {
			srb->function = AAC_SRB_FUNC_RESET_DEVICE;
			break;
		} else {
			ccb->ccb_h.status = CAM_REQ_CMP;
			xpt_done(ccb);
			return;
		}
	default:
		break;
	}

	srb->bus = camsc->inf->BusNumber; /* Bus number relative to the card */
	srb->target = ccb->ccb_h.target_id;
	srb->lun = ccb->ccb_h.target_lun;
	srb->timeout = ccb->ccb_h.timeout;	/* XXX */
	srb->retry_limit = 0;

	cm->cm_complete = aac_cam_complete;
	cm->cm_private = ccb;
	cm->cm_timestamp = time_uptime;

	fib->Header.XferState =
	    AAC_FIBSTATE_HOSTOWNED	|
	    AAC_FIBSTATE_INITIALISED	|
	    AAC_FIBSTATE_FROMHOST	|
	    AAC_FIBSTATE_REXPECTED	|
	    AAC_FIBSTATE_NORM;
	fib->Header.Size = sizeof(struct aac_fib_header) +
	    sizeof(struct aac_srb);

	aac_enqueue_ready(cm);
	aac_startio(cm->cm_sc);
}