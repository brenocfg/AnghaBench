#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ccb_hdr {int /*<<< orphan*/  status; } ;
union ccb {struct ccb_hdr ccb_h; } ;
struct vtscsi_softc {int dummy; } ;
struct vtscsi_request {union ccb* vsr_ccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_RESRC_UNAVAIL ; 
 int EAGAIN ; 
 int /*<<< orphan*/  VTSCSI_ERROR ; 
 int /*<<< orphan*/  VTSCSI_REQUEST ; 
 struct vtscsi_request* vtscsi_dequeue_request (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,int,struct vtscsi_request*,union ccb*) ; 
 int /*<<< orphan*/  vtscsi_enqueue_request (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int vtscsi_execute_abort_task_cmd (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int /*<<< orphan*/  vtscsi_freeze_simq (struct vtscsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vtscsi_cam_abort(struct vtscsi_softc *sc, union ccb *ccb)
{
	struct vtscsi_request *req;
	struct ccb_hdr *ccbh;
	int error;

	ccbh = &ccb->ccb_h;

	req = vtscsi_dequeue_request(sc);
	if (req == NULL) {
		error = EAGAIN;
		vtscsi_freeze_simq(sc, VTSCSI_REQUEST);
		goto fail;
	}

	req->vsr_ccb = ccb;

	error = vtscsi_execute_abort_task_cmd(sc, req);
	if (error == 0)
		return;

	vtscsi_enqueue_request(sc, req);

fail:
	vtscsi_dprintf(sc, VTSCSI_ERROR, "error=%d req=%p ccb=%p\n",
	    error, req, ccb);

	if (error == EAGAIN)
		ccbh->status = CAM_RESRC_UNAVAIL;
	else
		ccbh->status = CAM_REQ_CMP_ERR;

	xpt_done(ccb);
}