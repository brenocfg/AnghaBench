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
struct ccb_hdr {int /*<<< orphan*/  status; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
union ccb {struct ccb_hdr ccb_h; } ;
struct vtscsi_softc {int dummy; } ;
struct virtio_scsi_ctrl_tmf_resp {scalar_t__ response; } ;
struct vtscsi_request {struct virtio_scsi_ctrl_tmf_resp vsr_tmf_resp; union ccb* vsr_ccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_SENT_BDR ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 scalar_t__ VIRTIO_SCSI_S_FUNCTION_COMPLETE ; 
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 int /*<<< orphan*/  vtscsi_announce (struct vtscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,struct vtscsi_request*,union ccb*,scalar_t__) ; 
 int /*<<< orphan*/  vtscsi_enqueue_request (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vtscsi_complete_reset_dev_cmd(struct vtscsi_softc *sc,
    struct vtscsi_request *req)
{
	union ccb *ccb;
	struct ccb_hdr *ccbh;
	struct virtio_scsi_ctrl_tmf_resp *tmf_resp;

	ccb = req->vsr_ccb;
	ccbh = &ccb->ccb_h;
	tmf_resp = &req->vsr_tmf_resp;

	vtscsi_dprintf(sc, VTSCSI_TRACE, "req=%p ccb=%p response=%d\n",
	    req, ccb, tmf_resp->response);

	if (tmf_resp->response == VIRTIO_SCSI_S_FUNCTION_COMPLETE) {
		ccbh->status = CAM_REQ_CMP;
		vtscsi_announce(sc, AC_SENT_BDR, ccbh->target_id,
		    ccbh->target_lun);
	} else
		ccbh->status = CAM_REQ_CMP_ERR;

	xpt_done(ccb);
	vtscsi_enqueue_request(sc, req);
}