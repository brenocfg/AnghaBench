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
struct TYPE_4__ {int flags; scalar_t__ status; int /*<<< orphan*/  path; int /*<<< orphan*/ * ccb_pvscsi_sc; int /*<<< orphan*/ * ccb_pvscsi_hcb; } ;
struct TYPE_3__ {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; scalar_t__ resid; scalar_t__ dxfer_len; scalar_t__ scsi_status; } ;
union ccb {TYPE_2__ ccb_h; TYPE_1__ csio; } ;
typedef  scalar_t__ uint32_t ;
struct pvscsi_softc {scalar_t__ frozen; int /*<<< orphan*/  dev; int /*<<< orphan*/  buffer_dmat; } ;
struct pvscsi_ring_cmp_desc {scalar_t__ host_status; scalar_t__ scsi_status; scalar_t__ context; int /*<<< orphan*/  sense_len; scalar_t__ data_len; } ;
struct pvscsi_hcb {int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/  dma_map; union ccb* ccb; int /*<<< orphan*/  callout; } ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;

/* Variables and functions */
#define  BTSTAT_ABORTQUEUE 156 
#define  BTSTAT_BADMSG 155 
#define  BTSTAT_BUSFREE 154 
#define  BTSTAT_BUSRESET 153 
#define  BTSTAT_DATARUN 152 
#define  BTSTAT_DATA_UNDERRUN 151 
#define  BTSTAT_DISCONNECT 150 
#define  BTSTAT_HAHARDWARE 149 
#define  BTSTAT_HASOFTWARE 148 
#define  BTSTAT_HATIMEOUT 147 
#define  BTSTAT_INVPARAM 146 
#define  BTSTAT_INVPHASE 145 
#define  BTSTAT_LINKED_COMMAND_COMPLETED 144 
#define  BTSTAT_LINKED_COMMAND_COMPLETED_WITH_FLAG 143 
#define  BTSTAT_LUNMISMATCH 142 
#define  BTSTAT_NORESPONSE 141 
#define  BTSTAT_RECVRST 140 
#define  BTSTAT_SCSIPARITY 139 
#define  BTSTAT_SELTIMEO 138 
#define  BTSTAT_SENSFAILED 137 
#define  BTSTAT_SENTRST 136 
#define  BTSTAT_SUCCESS 135 
#define  BTSTAT_TAGREJECT 134 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 scalar_t__ CAM_AUTOSENSE_FAIL ; 
 scalar_t__ CAM_AUTOSNS_VALID ; 
 scalar_t__ CAM_DATA_RUN_ERR ; 
 scalar_t__ CAM_DEV_QFRZN ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 scalar_t__ CAM_NO_HBA ; 
 scalar_t__ CAM_RELEASE_SIMQ ; 
 scalar_t__ CAM_REQUEUE_REQ ; 
 scalar_t__ CAM_REQ_ABORTED ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_REQ_CMP_ERR ; 
 scalar_t__ CAM_SCSI_BUS_RESET ; 
 scalar_t__ CAM_SCSI_STATUS_ERROR ; 
 scalar_t__ CAM_SEL_TIMEOUT ; 
 scalar_t__ CAM_SEQUENCE_FAIL ; 
 scalar_t__ CAM_SIM_QUEUED ; 
 scalar_t__ CAM_STATUS_MASK ; 
 scalar_t__ CAM_UNCOR_PARITY ; 
 scalar_t__ CAM_UNEXP_BUSFREE ; 
 int /*<<< orphan*/  DEBUG_PRINTF (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SCSI_STATUS_BUSY 133 
#define  SCSI_STATUS_CHECK_COND 132 
#define  SCSI_STATUS_CMD_TERMINATED 131 
#define  SCSI_STATUS_OK 130 
#define  SCSI_STATUS_QUEUE_FULL 129 
#define  SCSI_STATUS_TASK_ABORTED 128 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct pvscsi_hcb* pvscsi_context_to_hcb (struct pvscsi_softc*,scalar_t__) ; 
 int /*<<< orphan*/  pvscsi_hcb_put (struct pvscsi_softc*,struct pvscsi_hcb*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pvscsi_process_completion(struct pvscsi_softc *sc,
    struct pvscsi_ring_cmp_desc *e)
{
	struct pvscsi_hcb *hcb;
	union ccb *ccb;
	uint32_t status;
	uint32_t btstat;
	uint32_t sdstat;
	bus_dmasync_op_t op;

	hcb = pvscsi_context_to_hcb(sc, e->context);

	callout_stop(&hcb->callout);

	ccb = hcb->ccb;

	btstat = e->host_status;
	sdstat = e->scsi_status;

	ccb->csio.scsi_status = sdstat;
	ccb->csio.resid = ccb->csio.dxfer_len - e->data_len;

	if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN) {
			op = BUS_DMASYNC_POSTREAD;
		} else {
			op = BUS_DMASYNC_POSTWRITE;
		}
		bus_dmamap_sync(sc->buffer_dmat, hcb->dma_map, op);
		bus_dmamap_unload(sc->buffer_dmat, hcb->dma_map);
	}

	if (btstat == BTSTAT_SUCCESS && sdstat == SCSI_STATUS_OK) {
		DEBUG_PRINTF(3, sc->dev,
		    "completing command context %llx success\n",
		    (unsigned long long)e->context);
		ccb->csio.resid = 0;
		status = CAM_REQ_CMP;
	} else {
		switch (btstat) {
		case BTSTAT_SUCCESS:
		case BTSTAT_LINKED_COMMAND_COMPLETED:
		case BTSTAT_LINKED_COMMAND_COMPLETED_WITH_FLAG:
			switch (sdstat) {
			case SCSI_STATUS_OK:
				ccb->csio.resid = 0;
				status = CAM_REQ_CMP;
				break;
			case SCSI_STATUS_CHECK_COND:
				status = CAM_SCSI_STATUS_ERROR;

				if (ccb->csio.sense_len != 0) {
					status |= CAM_AUTOSNS_VALID;

					memset(&ccb->csio.sense_data, 0,
					    sizeof(ccb->csio.sense_data));
					memcpy(&ccb->csio.sense_data,
					    hcb->sense_buffer,
					    MIN(ccb->csio.sense_len,
						e->sense_len));
				}
				break;
			case SCSI_STATUS_BUSY:
			case SCSI_STATUS_QUEUE_FULL:
				status = CAM_REQUEUE_REQ;
				break;
			case SCSI_STATUS_CMD_TERMINATED:
			case SCSI_STATUS_TASK_ABORTED:
				status = CAM_REQ_ABORTED;
				break;
			default:
				DEBUG_PRINTF(1, sc->dev,
				    "ccb: %p sdstat=0x%x\n", ccb, sdstat);
				status = CAM_SCSI_STATUS_ERROR;
				break;
			}
			break;
		case BTSTAT_SELTIMEO:
			status = CAM_SEL_TIMEOUT;
			break;
		case BTSTAT_DATARUN:
		case BTSTAT_DATA_UNDERRUN:
			status = CAM_DATA_RUN_ERR;
			break;
		case BTSTAT_ABORTQUEUE:
		case BTSTAT_HATIMEOUT:
			status = CAM_REQUEUE_REQ;
			break;
		case BTSTAT_NORESPONSE:
		case BTSTAT_SENTRST:
		case BTSTAT_RECVRST:
		case BTSTAT_BUSRESET:
			status = CAM_SCSI_BUS_RESET;
			break;
		case BTSTAT_SCSIPARITY:
			status = CAM_UNCOR_PARITY;
			break;
		case BTSTAT_BUSFREE:
			status = CAM_UNEXP_BUSFREE;
			break;
		case BTSTAT_INVPHASE:
			status = CAM_SEQUENCE_FAIL;
			break;
		case BTSTAT_SENSFAILED:
			status = CAM_AUTOSENSE_FAIL;
			break;
		case BTSTAT_LUNMISMATCH:
		case BTSTAT_TAGREJECT:
		case BTSTAT_DISCONNECT:
		case BTSTAT_BADMSG:
		case BTSTAT_INVPARAM:
			status = CAM_REQ_CMP_ERR;
			break;
		case BTSTAT_HASOFTWARE:
		case BTSTAT_HAHARDWARE:
			status = CAM_NO_HBA;
			break;
		default:
			device_printf(sc->dev, "unknown hba status: 0x%x\n",
			    btstat);
			status = CAM_NO_HBA;
			break;
		}

		DEBUG_PRINTF(3, sc->dev,
		    "completing command context %llx btstat %x sdstat %x - status %x\n",
		    (unsigned long long)e->context, btstat, sdstat, status);
	}

	ccb->ccb_h.ccb_pvscsi_hcb = NULL;
	ccb->ccb_h.ccb_pvscsi_sc = NULL;
	pvscsi_hcb_put(sc, hcb);

	ccb->ccb_h.status =
	    status | (ccb->ccb_h.status & ~(CAM_STATUS_MASK | CAM_SIM_QUEUED));

	if (sc->frozen) {
		ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
		sc->frozen = 0;
	}

	if (status != CAM_REQ_CMP) {
		ccb->ccb_h.status |= CAM_DEV_QFRZN;
		xpt_freeze_devq(ccb->ccb_h.path, /*count*/ 1);
	}
	xpt_done(ccb);
}