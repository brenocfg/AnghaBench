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
typedef  scalar_t__ uint8_t ;
struct vtscsi_softc {int vtscsi_flags; } ;
struct virtio_scsi_ctrl_tmf_resp {scalar_t__ response; } ;
struct vtscsi_request {scalar_t__ vsr_state; struct vtscsi_request* vsr_timedout_req; struct virtio_scsi_ctrl_tmf_resp vsr_tmf_resp; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_SCSI_S_FUNCTION_COMPLETE ; 
 int VTSCSI_FLAG_DETACH ; 
 int VTSCSI_FLAG_RESET ; 
 scalar_t__ VTSCSI_REQ_STATE_TIMEDOUT ; 
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,struct vtscsi_request*,struct vtscsi_request*,scalar_t__) ; 
 int /*<<< orphan*/  vtscsi_enqueue_request (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int /*<<< orphan*/  vtscsi_reset_bus (struct vtscsi_softc*) ; 

__attribute__((used)) static void
vtscsi_complete_abort_timedout_scsi_cmd(struct vtscsi_softc *sc,
    struct vtscsi_request *req)
{
	struct virtio_scsi_ctrl_tmf_resp *tmf_resp;
	struct vtscsi_request *to_req;
	uint8_t response;

	tmf_resp = &req->vsr_tmf_resp;
	response = tmf_resp->response;
	to_req = req->vsr_timedout_req;

	vtscsi_dprintf(sc, VTSCSI_TRACE, "req=%p to_req=%p response=%d\n",
	    req, to_req, response);

	vtscsi_enqueue_request(sc, req);

	/*
	 * The timedout request could have completed between when the
	 * abort task was sent and when the host processed it.
	 */
	if (to_req->vsr_state != VTSCSI_REQ_STATE_TIMEDOUT)
		return;

	/* The timedout request was successfully aborted. */
	if (response == VIRTIO_SCSI_S_FUNCTION_COMPLETE)
		return;

	/* Don't bother if the device is going away. */
	if (sc->vtscsi_flags & VTSCSI_FLAG_DETACH)
		return;

	/* The timedout request will be aborted by the reset. */
	if (sc->vtscsi_flags & VTSCSI_FLAG_RESET)
		return;

	vtscsi_reset_bus(sc);
}