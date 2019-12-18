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
struct TYPE_2__ {int /*<<< orphan*/  scsi_cmd_timeouts; } ;
struct vtscsi_softc {int vtscsi_flags; TYPE_1__ vtscsi_stats; int /*<<< orphan*/  vtscsi_request_vq; } ;
struct vtscsi_request {scalar_t__ vsr_state; int vsr_flags; int /*<<< orphan*/  vsr_ccb; struct vtscsi_softc* vsr_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_ERROR ; 
 int VTSCSI_FLAG_DETACH ; 
 int /*<<< orphan*/  VTSCSI_INFO ; 
 int VTSCSI_REQ_FLAG_TIMEOUT_SET ; 
 scalar_t__ VTSCSI_REQ_STATE_FREE ; 
 scalar_t__ VTSCSI_REQ_STATE_INUSE ; 
 scalar_t__ VTSCSI_REQ_STATE_TIMEDOUT ; 
 scalar_t__ vtscsi_abort_timedout_scsi_cmd (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int /*<<< orphan*/  vtscsi_complete_vq (struct vtscsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  vtscsi_reset_bus (struct vtscsi_softc*) ; 

__attribute__((used)) static void
vtscsi_timedout_scsi_cmd(void *xreq)
{
	struct vtscsi_softc *sc;
	struct vtscsi_request *to_req;

	to_req = xreq;
	sc = to_req->vsr_softc;

	vtscsi_dprintf(sc, VTSCSI_INFO, "timedout req=%p ccb=%p state=%#x\n",
	    to_req, to_req->vsr_ccb, to_req->vsr_state);

	/* Don't bother if the device is going away. */
	if (sc->vtscsi_flags & VTSCSI_FLAG_DETACH)
		return;

	/*
	 * Bail if the request is not in use. We likely raced when
	 * stopping the callout handler or it has already been aborted.
	 */
	if (to_req->vsr_state != VTSCSI_REQ_STATE_INUSE ||
	    (to_req->vsr_flags & VTSCSI_REQ_FLAG_TIMEOUT_SET) == 0)
		return;

	/*
	 * Complete the request queue in case the timedout request is
	 * actually just pending.
	 */
	vtscsi_complete_vq(sc, sc->vtscsi_request_vq);
	if (to_req->vsr_state == VTSCSI_REQ_STATE_FREE)
		return;

	sc->vtscsi_stats.scsi_cmd_timeouts++;
	to_req->vsr_state = VTSCSI_REQ_STATE_TIMEDOUT;

	if (vtscsi_abort_timedout_scsi_cmd(sc, to_req) == 0)
		return;

	vtscsi_dprintf(sc, VTSCSI_ERROR, "resetting bus\n");
	vtscsi_reset_bus(sc);
}