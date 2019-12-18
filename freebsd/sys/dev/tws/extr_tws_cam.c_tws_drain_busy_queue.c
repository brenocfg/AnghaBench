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
struct tws_softc {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  sim_lock; } ;
struct tws_request {scalar_t__ ccb_ptr; int /*<<< orphan*/  sc; int /*<<< orphan*/  error_code; int /*<<< orphan*/  timeout; int /*<<< orphan*/  request_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  CAM_SCSI_BUS_RESET ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  TWS_BUSY_Q ; 
 int /*<<< orphan*/  TWS_FREE_Q ; 
 int /*<<< orphan*/  TWS_REQ_RET_RESET ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_q_insert_tail (struct tws_softc*,struct tws_request*,int /*<<< orphan*/ ) ; 
 struct tws_request* tws_q_remove_tail (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_unmap_request (int /*<<< orphan*/ ,struct tws_request*) ; 
 int /*<<< orphan*/  xpt_done (scalar_t__) ; 

__attribute__((used)) static void
tws_drain_busy_queue(struct tws_softc *sc)
{
    struct tws_request *req;
    union ccb          *ccb;
    TWS_TRACE_DEBUG(sc, "entry", 0, 0);

    mtx_lock(&sc->q_lock);
    req = tws_q_remove_tail(sc, TWS_BUSY_Q);
    mtx_unlock(&sc->q_lock);
    while ( req ) {
        TWS_TRACE_DEBUG(sc, "moved to TWS_COMPLETE_Q", 0, req->request_id);
	callout_stop(&req->timeout);

        req->error_code = TWS_REQ_RET_RESET;
        ccb = (union ccb *)(req->ccb_ptr);

        ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
        ccb->ccb_h.status |=  CAM_REQUEUE_REQ;
        ccb->ccb_h.status |=  CAM_SCSI_BUS_RESET;

        tws_unmap_request(req->sc, req);

        mtx_lock(&sc->sim_lock);
        xpt_done(req->ccb_ptr);
        mtx_unlock(&sc->sim_lock);

        mtx_lock(&sc->q_lock);
        tws_q_insert_tail(sc, req, TWS_FREE_Q);
        req = tws_q_remove_tail(sc, TWS_BUSY_Q);
        mtx_unlock(&sc->q_lock);
    } 
}