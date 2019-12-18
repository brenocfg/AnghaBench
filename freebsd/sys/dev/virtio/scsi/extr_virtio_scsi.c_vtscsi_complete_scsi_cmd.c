#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vtscsi_softc {int dummy; } ;
struct virtio_scsi_cmd_resp {int dummy; } ;
struct vtscsi_request {int vsr_flags; scalar_t__ vsr_state; TYPE_1__* vsr_ccb; int /*<<< orphan*/  vsr_callout; struct virtio_scsi_cmd_resp vsr_cmd_resp; } ;
struct ccb_hdr {int status; int /*<<< orphan*/  path; struct vtscsi_request* ccbh_vtscsi_req; } ;
struct ccb_scsiio {struct ccb_hdr ccb_h; } ;
typedef  int cam_status ;
struct TYPE_2__ {struct ccb_scsiio csio; } ;

/* Variables and functions */
 int CAM_CMD_TIMEOUT ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQ_ABORTED ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VTSCSI_REQUEST ; 
 int VTSCSI_REQUEST_VQ ; 
 int VTSCSI_REQ_FLAG_TIMEOUT_SET ; 
 scalar_t__ VTSCSI_REQ_STATE_TIMEDOUT ; 
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int vtscsi_complete_scsi_cmd_response (struct vtscsi_softc*,struct ccb_scsiio*,struct virtio_scsi_cmd_resp*) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,struct vtscsi_request*,struct ccb_hdr*,int) ; 
 int /*<<< orphan*/  vtscsi_enqueue_request (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int vtscsi_scsi_cmd_cam_status (struct virtio_scsi_cmd_resp*) ; 
 scalar_t__ vtscsi_thaw_simq (struct vtscsi_softc*,int) ; 
 int /*<<< orphan*/  xpt_done (TYPE_1__*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vtscsi_complete_scsi_cmd(struct vtscsi_softc *sc, struct vtscsi_request *req)
{
	struct ccb_hdr *ccbh;
	struct ccb_scsiio *csio;
	struct virtio_scsi_cmd_resp *cmd_resp;
	cam_status status;

	csio = &req->vsr_ccb->csio;
	ccbh = &csio->ccb_h;
	cmd_resp = &req->vsr_cmd_resp;

	KASSERT(ccbh->ccbh_vtscsi_req == req,
	    ("ccb %p req mismatch %p/%p", ccbh, ccbh->ccbh_vtscsi_req, req));

	if (req->vsr_flags & VTSCSI_REQ_FLAG_TIMEOUT_SET)
		callout_stop(&req->vsr_callout);

	status = vtscsi_scsi_cmd_cam_status(cmd_resp);
	if (status == CAM_REQ_ABORTED) {
		if (req->vsr_state == VTSCSI_REQ_STATE_TIMEDOUT)
			status = CAM_CMD_TIMEOUT;
	} else if (status == CAM_REQ_CMP)
		status = vtscsi_complete_scsi_cmd_response(sc, csio, cmd_resp);

	if ((status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		status |= CAM_DEV_QFRZN;
		xpt_freeze_devq(ccbh->path, 1);
	}

	if (vtscsi_thaw_simq(sc, VTSCSI_REQUEST | VTSCSI_REQUEST_VQ) != 0)
		status |= CAM_RELEASE_SIMQ;

	vtscsi_dprintf(sc, VTSCSI_TRACE, "req=%p ccb=%p status=%#x\n",
	    req, ccbh, status);

	ccbh->status = status;
	xpt_done(req->vsr_ccb);
	vtscsi_enqueue_request(sc, req);
}