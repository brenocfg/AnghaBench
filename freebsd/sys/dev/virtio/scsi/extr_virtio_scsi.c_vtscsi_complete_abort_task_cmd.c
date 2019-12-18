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
struct virtio_scsi_ctrl_tmf_resp {int response; } ;
struct vtscsi_request {struct virtio_scsi_ctrl_tmf_resp vsr_tmf_resp; union ccb* vsr_ccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_UA_ABORT ; 
#define  VIRTIO_SCSI_S_FUNCTION_COMPLETE 129 
#define  VIRTIO_SCSI_S_FUNCTION_REJECTED 128 
 int /*<<< orphan*/  vtscsi_enqueue_request (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vtscsi_complete_abort_task_cmd(struct vtscsi_softc *sc,
    struct vtscsi_request *req)
{
	union ccb *ccb;
	struct ccb_hdr *ccbh;
	struct virtio_scsi_ctrl_tmf_resp *tmf_resp;

	ccb = req->vsr_ccb;
	ccbh = &ccb->ccb_h;
	tmf_resp = &req->vsr_tmf_resp;

	switch (tmf_resp->response) {
	case VIRTIO_SCSI_S_FUNCTION_COMPLETE:
		ccbh->status = CAM_REQ_CMP;
		break;
	case VIRTIO_SCSI_S_FUNCTION_REJECTED:
		ccbh->status = CAM_UA_ABORT;
		break;
	default:
		ccbh->status = CAM_REQ_CMP_ERR;
		break;
	}

	xpt_done(ccb);
	vtscsi_enqueue_request(sc, req);
}