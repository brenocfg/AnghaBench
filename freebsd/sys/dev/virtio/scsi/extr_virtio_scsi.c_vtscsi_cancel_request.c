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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct vtscsi_softc {int vtscsi_flags; } ;
struct vtscsi_request {int vsr_flags; int /*<<< orphan*/  vsr_callout; union ccb* vsr_ccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_NO_HBA ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int VTSCSI_FLAG_DETACH ; 
 int /*<<< orphan*/  VTSCSI_LOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_LOCK_NOTOWNED (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_LOCK_OWNED (struct vtscsi_softc*) ; 
 int VTSCSI_REQ_FLAG_TIMEOUT_SET ; 
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 int /*<<< orphan*/  VTSCSI_UNLOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,struct vtscsi_request*,union ccb*) ; 
 int /*<<< orphan*/  vtscsi_enqueue_request (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vtscsi_cancel_request(struct vtscsi_softc *sc, struct vtscsi_request *req)
{
	union ccb *ccb;
	int detach;

	ccb = req->vsr_ccb;

	vtscsi_dprintf(sc, VTSCSI_TRACE, "req=%p ccb=%p\n", req, ccb);

	/*
	 * The callout must be drained when detaching since the request is
	 * about to be freed. The VTSCSI_MTX must not be held for this in
	 * case the callout is pending because there is a deadlock potential.
	 * Otherwise, the virtqueue is being drained because of a bus reset
	 * so we only need to attempt to stop the callouts.
	 */
	detach = (sc->vtscsi_flags & VTSCSI_FLAG_DETACH) != 0;
	if (detach != 0)
		VTSCSI_LOCK_NOTOWNED(sc);
	else
		VTSCSI_LOCK_OWNED(sc);

	if (req->vsr_flags & VTSCSI_REQ_FLAG_TIMEOUT_SET) {
		if (detach != 0)
			callout_drain(&req->vsr_callout);
		else
			callout_stop(&req->vsr_callout);
	}

	if (ccb != NULL) {
		if (detach != 0) {
			VTSCSI_LOCK(sc);
			ccb->ccb_h.status = CAM_NO_HBA;
		} else
			ccb->ccb_h.status = CAM_REQUEUE_REQ;
		xpt_done(ccb);
		if (detach != 0)
			VTSCSI_UNLOCK(sc);
	}

	vtscsi_enqueue_request(sc, req);
}