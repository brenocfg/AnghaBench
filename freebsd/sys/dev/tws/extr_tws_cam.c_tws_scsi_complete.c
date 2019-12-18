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
struct tws_softc {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  sim_lock; } ;
struct tws_request {TYPE_2__* ccb_ptr; struct tws_softc* sc; int /*<<< orphan*/  timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  TWS_BUSY_Q ; 
 int /*<<< orphan*/  TWS_FREE_Q ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_q_insert_tail (struct tws_softc*,struct tws_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_q_remove_request (struct tws_softc*,struct tws_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_unmap_request (struct tws_softc*,struct tws_request*) ; 
 int /*<<< orphan*/  xpt_done (TYPE_2__*) ; 

__attribute__((used)) static void
tws_scsi_complete(struct tws_request *req)
{
    struct tws_softc *sc = req->sc;

    mtx_lock(&sc->q_lock);
    tws_q_remove_request(sc, req, TWS_BUSY_Q);
    mtx_unlock(&sc->q_lock);

    callout_stop(&req->timeout);
    tws_unmap_request(req->sc, req);


    req->ccb_ptr->ccb_h.status = CAM_REQ_CMP;
    mtx_lock(&sc->sim_lock);
    xpt_done(req->ccb_ptr);
    mtx_unlock(&sc->sim_lock);

    mtx_lock(&sc->q_lock);
    tws_q_insert_tail(sc, req, TWS_FREE_Q);
    mtx_unlock(&sc->q_lock);
}