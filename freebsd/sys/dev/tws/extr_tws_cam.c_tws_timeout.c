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
struct tws_softc {int /*<<< orphan*/  sim; int /*<<< orphan*/  gen_lock; int /*<<< orphan*/  tws_dev; } ;
struct tws_request {scalar_t__ error_code; scalar_t__ type; struct tws_softc* sc; } ;

/* Variables and functions */
 scalar_t__ TWS_REQ_RET_RESET ; 
 scalar_t__ TWS_REQ_TYPE_PASSTHRU ; 
 scalar_t__ TWS_REQ_TYPE_SCSI_IO ; 
 scalar_t__ TWS_RESET ; 
 int /*<<< orphan*/  TWS_RESET_COMPLETE ; 
 int /*<<< orphan*/  TWS_RESET_START ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_assert_soft_reset (struct tws_softc*) ; 
 scalar_t__ tws_get_state (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_reinit (void*) ; 
 int /*<<< orphan*/  tws_reset_cb (void*) ; 
 int /*<<< orphan*/  tws_send_event (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_turn_off_interrupts (struct tws_softc*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int) ; 

void
tws_timeout(void *arg)
{
    struct tws_request *req = (struct tws_request *)arg;
    struct tws_softc *sc = req->sc;


    if ( req->error_code == TWS_REQ_RET_RESET ) {
        return;
    }

    mtx_lock(&sc->gen_lock);
    if ( req->error_code == TWS_REQ_RET_RESET ) {
        mtx_unlock(&sc->gen_lock);
        return;
    }

    if ( tws_get_state(sc) == TWS_RESET ) {
        mtx_unlock(&sc->gen_lock);
        return;
    }

    xpt_freeze_simq(sc->sim, 1);

    tws_send_event(sc, TWS_RESET_START);

    if (req->type == TWS_REQ_TYPE_SCSI_IO) {
        device_printf(sc->tws_dev, "I/O Request timed out... Resetting controller\n");
    } else if (req->type == TWS_REQ_TYPE_PASSTHRU) {
        device_printf(sc->tws_dev, "IOCTL Request timed out... Resetting controller\n");
    } else {
        device_printf(sc->tws_dev, "Internal Request timed out... Resetting controller\n");
    }

    tws_assert_soft_reset(sc);
    tws_turn_off_interrupts(sc);
    tws_reset_cb( (void*) sc );
    tws_reinit( (void*) sc );

//  device_printf(sc->tws_dev,  "Controller Reset complete!\n");
    tws_send_event(sc, TWS_RESET_COMPLETE);
    mtx_unlock(&sc->gen_lock);

    xpt_release_simq(sc->sim, 1);
}