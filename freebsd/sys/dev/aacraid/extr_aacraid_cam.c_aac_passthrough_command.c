#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* entries; } ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  timeout; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; TYPE_2__ sim_priv; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct TYPE_11__ {scalar_t__ dxfer_len; scalar_t__ data_ptr; TYPE_3__ cdb_io; int /*<<< orphan*/  cdb_len; } ;
union ccb {TYPE_6__ ccb_h; TYPE_4__ csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct cam_sim {int dummy; } ;
struct aac_srb {scalar_t__ retry_limit; int /*<<< orphan*/  timeout; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; scalar_t__ bus; scalar_t__ data_len; int /*<<< orphan*/  sg_map; int /*<<< orphan*/  cdb_len; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  flags; int /*<<< orphan*/  function; } ;
struct aac_softc {int flags; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_io_lock; } ;
struct aac_fib_header {int dummy; } ;
struct TYPE_14__ {int Size; int XferState; int /*<<< orphan*/  Command; } ;
struct aac_fib {TYPE_7__ Header; int /*<<< orphan*/ * data; } ;
struct aac_event {int /*<<< orphan*/  ev_type; union ccb* ev_arg; int /*<<< orphan*/  ev_callback; } ;
struct aac_command {int cm_flags; int /*<<< orphan*/  cm_sc; int /*<<< orphan*/  cm_timestamp; union ccb* cm_ccb; int /*<<< orphan*/  cm_complete; scalar_t__ cm_datalen; int /*<<< orphan*/ * cm_data; int /*<<< orphan*/ * cm_sgtable; struct aac_fib* cm_fib; } ;
struct aac_cam {TYPE_5__* inf; } ;
struct TYPE_12__ {scalar_t__ BusNumber; struct aac_softc* aac_sc; } ;
struct TYPE_8__ {struct aac_cam* ptr; } ;

/* Variables and functions */
 int AAC_CMD_DATAIN ; 
 int AAC_CMD_DATAOUT ; 
 int /*<<< orphan*/  AAC_EVENT_CMFREE ; 
 int AAC_FIBSTATE_ASYNC ; 
 int AAC_FIBSTATE_FAST_RESPONSE ; 
 int AAC_FIBSTATE_FROMHOST ; 
 int AAC_FIBSTATE_HOSTOWNED ; 
 int AAC_FIBSTATE_INITIALISED ; 
 int AAC_FIBSTATE_NORM ; 
 int AAC_FIBSTATE_REXPECTED ; 
 int AAC_FLAGS_SG_64BIT ; 
 int /*<<< orphan*/  AAC_SRB_FLAGS_DATA_IN ; 
 int /*<<< orphan*/  AAC_SRB_FLAGS_DATA_OUT ; 
 int /*<<< orphan*/  AAC_SRB_FLAGS_NO_DATA_XFER ; 
 int /*<<< orphan*/  AAC_SRB_FLAGS_UNSPECIFIED_DIRECTION ; 
 int /*<<< orphan*/  AAC_SRB_FUNC_EXECUTE_SCSI ; 
 int CAM_CDB_POINTER ; 
#define  CAM_DIR_IN 130 
 int CAM_DIR_MASK ; 
#define  CAM_DIR_NONE 129 
#define  CAM_DIR_OUT 128 
 int /*<<< orphan*/  CAM_RESRC_UNAVAIL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_AACRAIDCAM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ScsiPortCommand ; 
 int /*<<< orphan*/  ScsiPortCommandU64 ; 
 int /*<<< orphan*/  aac_cam_complete ; 
 int /*<<< orphan*/  aac_cam_event ; 
 int /*<<< orphan*/  aac_enqueue_ready (struct aac_command*) ; 
 int /*<<< orphan*/  aacraid_add_event (struct aac_softc*,struct aac_event*) ; 
 scalar_t__ aacraid_alloc_command (struct aac_softc*,struct aac_command**) ; 
 int /*<<< orphan*/  aacraid_startio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct aac_event* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_uptime ; 
 int /*<<< orphan*/  xpt_freeze_simq (struct cam_sim*,int) ; 

__attribute__((used)) static void
aac_passthrough_command(struct cam_sim *sim, union ccb *ccb)
{
	struct	aac_cam *camsc;
	struct	aac_softc *sc;
	struct	aac_command *cm;
	struct	aac_fib *fib;
	struct	aac_srb *srb;

	camsc = (struct aac_cam *)cam_sim_softc(sim);
	sc = camsc->inf->aac_sc;
	mtx_assert(&sc->aac_io_lock, MA_OWNED);

	if (aacraid_alloc_command(sc, &cm)) {
		struct aac_event *event;

		xpt_freeze_simq(sim, 1);
		ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
		ccb->ccb_h.sim_priv.entries[0].ptr = camsc;
		event = malloc(sizeof(struct aac_event), M_AACRAIDCAM,
		    M_NOWAIT | M_ZERO);
		if (event == NULL) {
			device_printf(sc->aac_dev,
			    "Warning, out of memory for event\n");
			return;
		}
		event->ev_callback = aac_cam_event;
		event->ev_arg = ccb;
		event->ev_type = AAC_EVENT_CMFREE;
		aacraid_add_event(sc, event);
		return;
	}

	fib = cm->cm_fib;
	switch (ccb->ccb_h.flags & CAM_DIR_MASK) {
	case CAM_DIR_IN:
		cm->cm_flags |= AAC_CMD_DATAIN;
		break;
	case CAM_DIR_OUT:
		cm->cm_flags |= AAC_CMD_DATAOUT;
		break;
	case CAM_DIR_NONE:
		break;
	default:
		cm->cm_flags |= AAC_CMD_DATAIN | AAC_CMD_DATAOUT;
		break;
	}

	srb = (struct aac_srb *)&fib->data[0];
	srb->function = AAC_SRB_FUNC_EXECUTE_SCSI;
	if (cm->cm_flags & (AAC_CMD_DATAIN|AAC_CMD_DATAOUT)) 
		srb->flags = AAC_SRB_FLAGS_UNSPECIFIED_DIRECTION;
	if (cm->cm_flags & AAC_CMD_DATAIN) 
		srb->flags = AAC_SRB_FLAGS_DATA_IN;
	else if (cm->cm_flags & AAC_CMD_DATAOUT) 
		srb->flags = AAC_SRB_FLAGS_DATA_OUT;
	else  
		srb->flags = AAC_SRB_FLAGS_NO_DATA_XFER;

	/*
	 * Copy the CDB into the SRB.  It's only 6-16 bytes,
	 * so a copy is not too expensive.
	 */
	srb->cdb_len = ccb->csio.cdb_len;
	if (ccb->ccb_h.flags & CAM_CDB_POINTER)
		bcopy(ccb->csio.cdb_io.cdb_ptr, (u_int8_t *)&srb->cdb[0],
			srb->cdb_len);
	else
		bcopy(ccb->csio.cdb_io.cdb_bytes, (u_int8_t *)&srb->cdb[0],
			srb->cdb_len);

	/* Set command */
	fib->Header.Command = (sc->flags & AAC_FLAGS_SG_64BIT) ? 
		ScsiPortCommandU64 : ScsiPortCommand;
	fib->Header.Size = sizeof(struct aac_fib_header) +
			sizeof(struct aac_srb);

	/* Map the s/g list */
	cm->cm_sgtable = &srb->sg_map;
	if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
		/*
		 * Arrange things so that the S/G
		 * map will get set up automagically
		 */
		cm->cm_data = (void *)ccb->csio.data_ptr;
		cm->cm_datalen = ccb->csio.dxfer_len;
		srb->data_len = ccb->csio.dxfer_len;
	} else {
		cm->cm_data = NULL;
		cm->cm_datalen = 0;
		srb->data_len = 0;
	}

	srb->bus = camsc->inf->BusNumber - 1; /* Bus no. rel. to the card */
	srb->target = ccb->ccb_h.target_id;
	srb->lun = ccb->ccb_h.target_lun;
	srb->timeout = ccb->ccb_h.timeout;	/* XXX */
	srb->retry_limit = 0;

	cm->cm_complete = aac_cam_complete;
	cm->cm_ccb = ccb;
	cm->cm_timestamp = time_uptime;

	fib->Header.XferState =
			AAC_FIBSTATE_HOSTOWNED	|
			AAC_FIBSTATE_INITIALISED	|
			AAC_FIBSTATE_FROMHOST	|
			AAC_FIBSTATE_REXPECTED	|
			AAC_FIBSTATE_NORM	|
			AAC_FIBSTATE_ASYNC	 |
			AAC_FIBSTATE_FAST_RESPONSE;

	aac_enqueue_ready(cm);
	aacraid_startio(cm->cm_sc);
}