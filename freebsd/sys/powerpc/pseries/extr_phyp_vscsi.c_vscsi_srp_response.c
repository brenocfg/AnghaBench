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
struct TYPE_4__ {scalar_t__ scsi_status; scalar_t__ resid; scalar_t__ sense_len; scalar_t__ sense_resid; int /*<<< orphan*/  sense_data; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  status; int /*<<< orphan*/  path; } ;
union ccb {TYPE_2__ csio; TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vscsi_xfer {union ccb* ccb; int /*<<< orphan*/  dmamap; scalar_t__ srp_iu_offset; struct vscsi_softc* sc; } ;
struct vscsi_softc {int /*<<< orphan*/  data_tag; scalar_t__ srp_iu_queue; } ;
struct vscsi_crq {scalar_t__ status; } ;
struct srp_rsp {scalar_t__ status; int flags; scalar_t__ data_in_resid; scalar_t__ data_out_resid; scalar_t__ sense_data_len; scalar_t__ response_data_len; int /*<<< orphan*/ * data_payload; } ;
struct scsi_sense_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  CAM_AUTOSNS_VALID ; 
 int /*<<< orphan*/  CAM_DEV_QFRZN ; 
#define  CAM_DIR_IN 129 
 int CAM_DIR_MASK ; 
#define  CAM_DIR_OUT 128 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_SCSI_STATUS_ERROR ; 
 scalar_t__ SCSI_STATUS_OK ; 
 int SRP_DIOVER ; 
 int SRP_DIUNDER ; 
 int SRP_DOOVER ; 
 int SRP_DOUNDER ; 
 int SRP_RSPVALID ; 
 int SRP_SNSVALID ; 
 size_t be32toh (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,scalar_t__) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vscsi_srp_response(struct vscsi_xfer *xp, struct vscsi_crq *crq)
{
	union ccb *ccb = xp->ccb;
	struct vscsi_softc *sc = xp->sc;
	struct srp_rsp *rsp;
	uint32_t sense_len;

	/* SRP response packet in original request */
	rsp = (struct srp_rsp *)((uint8_t *)sc->srp_iu_queue +
	    (uintptr_t)xp->srp_iu_offset);
	ccb->csio.scsi_status = rsp->status;
	if (ccb->csio.scsi_status == SCSI_STATUS_OK)
		ccb->ccb_h.status = CAM_REQ_CMP;
	else
		ccb->ccb_h.status = CAM_SCSI_STATUS_ERROR;
#ifdef NOTYET
	/* Collect fast fail codes */
	if (crq->status != 0)
		ccb->ccb_h.status = CAM_REQ_CMP_ERR;
#endif

	if (ccb->ccb_h.status != CAM_REQ_CMP) {
		ccb->ccb_h.status |= CAM_DEV_QFRZN;
		xpt_freeze_devq(ccb->ccb_h.path, /*count*/ 1);
	}

	if (!(rsp->flags & SRP_RSPVALID))
		rsp->response_data_len = 0;
	if (!(rsp->flags & SRP_SNSVALID))
		rsp->sense_data_len = 0;
	if (!(rsp->flags & (SRP_DOOVER | SRP_DOUNDER)))
		rsp->data_out_resid = 0;
	if (!(rsp->flags & (SRP_DIOVER | SRP_DIUNDER)))
		rsp->data_in_resid = 0;

	if (rsp->flags & SRP_SNSVALID) {
		bzero(&ccb->csio.sense_data, sizeof(struct scsi_sense_data));
		ccb->ccb_h.status |= CAM_AUTOSNS_VALID;
		sense_len = min(be32toh(rsp->sense_data_len),
		    ccb->csio.sense_len);
		memcpy(&ccb->csio.sense_data,
		    &rsp->data_payload[be32toh(rsp->response_data_len)],
		    sense_len);
		ccb->csio.sense_resid = ccb->csio.sense_len -
		    be32toh(rsp->sense_data_len);
	}

	switch (ccb->ccb_h.flags & CAM_DIR_MASK) {
	case CAM_DIR_OUT:
		ccb->csio.resid = rsp->data_out_resid;
		break;
	case CAM_DIR_IN:
		ccb->csio.resid = rsp->data_in_resid;
		break;
	}

	bus_dmamap_sync(sc->data_tag, xp->dmamap, BUS_DMASYNC_POSTREAD);
	bus_dmamap_unload(sc->data_tag, xp->dmamap);
	xpt_done(ccb);
	xp->ccb = NULL;
}