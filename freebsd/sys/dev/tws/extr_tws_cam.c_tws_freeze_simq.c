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
struct tws_softc {int /*<<< orphan*/  sim; } ;
struct tws_request {scalar_t__ type; scalar_t__ ccb_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_RELEASE_SIMQ ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 scalar_t__ TWS_REQ_TYPE_SCSI_IO ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tws_freeze_simq(struct tws_softc *sc, struct tws_request *req)
{
    /* Only for IO commands */
    if (req->type == TWS_REQ_TYPE_SCSI_IO) {
        union ccb   *ccb = (union ccb *)(req->ccb_ptr);

        xpt_freeze_simq(sc->sim, 1);
        ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
        ccb->ccb_h.status |= CAM_REQUEUE_REQ;
    }
}