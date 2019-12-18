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
struct vtscsi_softc {struct sglist* vtscsi_sglist; } ;
struct virtio_scsi_ctrl_tmf_resp {int response; } ;
struct vtscsi_request {int /*<<< orphan*/  vsr_complete; struct vtscsi_request* vsr_timedout_req; struct virtio_scsi_ctrl_tmf_resp vsr_tmf_resp; struct virtio_scsi_ctrl_tmf_resp vsr_tmf_req; TYPE_1__* vsr_ccb; } ;
struct virtio_scsi_ctrl_tmf_req {int response; } ;
struct sglist {int dummy; } ;
struct ccb_hdr {int dummy; } ;
struct TYPE_2__ {struct ccb_hdr ccb_h; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  VIRTIO_SCSI_T_TMF_ABORT_TASK ; 
 int /*<<< orphan*/  VTSCSI_ERROR ; 
 int /*<<< orphan*/  VTSCSI_EXECUTE_ASYNC ; 
 int /*<<< orphan*/  sglist_append (struct sglist*,struct virtio_scsi_ctrl_tmf_resp*,int) ; 
 int /*<<< orphan*/  sglist_reset (struct sglist*) ; 
 int /*<<< orphan*/  vtscsi_complete_abort_timedout_scsi_cmd ; 
 struct vtscsi_request* vtscsi_dequeue_request (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,int,struct vtscsi_request*,struct vtscsi_request*,struct ccb_hdr*) ; 
 int /*<<< orphan*/  vtscsi_enqueue_request (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int vtscsi_execute_ctrl_req (struct vtscsi_softc*,struct vtscsi_request*,struct sglist*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_init_ctrl_tmf_req (struct ccb_hdr*,int /*<<< orphan*/ ,uintptr_t,struct virtio_scsi_ctrl_tmf_resp*) ; 

__attribute__((used)) static int
vtscsi_abort_timedout_scsi_cmd(struct vtscsi_softc *sc,
    struct vtscsi_request *to_req)
{
	struct sglist *sg;
	struct ccb_hdr *to_ccbh;
	struct vtscsi_request *req;
	struct virtio_scsi_ctrl_tmf_req *tmf_req;
	struct virtio_scsi_ctrl_tmf_resp *tmf_resp;
	int error;

	sg = sc->vtscsi_sglist;
	to_ccbh = &to_req->vsr_ccb->ccb_h;

	req = vtscsi_dequeue_request(sc);
	if (req == NULL) {
		error = ENOBUFS;
		goto fail;
	}

	tmf_req = &req->vsr_tmf_req;
	tmf_resp = &req->vsr_tmf_resp;

	vtscsi_init_ctrl_tmf_req(to_ccbh, VIRTIO_SCSI_T_TMF_ABORT_TASK,
	    (uintptr_t) to_ccbh, tmf_req);

	sglist_reset(sg);
	sglist_append(sg, tmf_req, sizeof(struct virtio_scsi_ctrl_tmf_req));
	sglist_append(sg, tmf_resp, sizeof(struct virtio_scsi_ctrl_tmf_resp));

	req->vsr_timedout_req = to_req;
	req->vsr_complete = vtscsi_complete_abort_timedout_scsi_cmd;
	tmf_resp->response = -1;

	error = vtscsi_execute_ctrl_req(sc, req, sg, 1, 1,
	    VTSCSI_EXECUTE_ASYNC);
	if (error == 0)
		return (0);

	vtscsi_enqueue_request(sc, req);

fail:
	vtscsi_dprintf(sc, VTSCSI_ERROR, "error=%d req=%p "
	    "timedout req=%p ccb=%p\n", error, req, to_req, to_ccbh);

	return (error);
}