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
struct tws_softc {int obfl_q_overrun; int /*<<< orphan*/  is64bit; int /*<<< orphan*/  tws_dev; int /*<<< orphan*/  gen_lock; } ;

/* Variables and functions */
 int TWS_RESET_TIMEOUT ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_sleep (struct tws_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tws_assert_soft_reset (struct tws_softc*) ; 
 scalar_t__ tws_ctlr_ready (struct tws_softc*) ; 
 scalar_t__ tws_init_connect (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_init_obfl_q (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_queue_depth ; 
 int /*<<< orphan*/  tws_turn_on_interrupts (struct tws_softc*) ; 
 int /*<<< orphan*/  wakeup_one (struct tws_softc*) ; 

__attribute__((used)) static void
tws_reinit(void *arg)
{
    struct tws_softc *sc = (struct tws_softc *)arg;
    int timeout_val=0;
    int try=2;
    int done=0;


//  device_printf(sc->tws_dev,  "Waiting for Controller Ready\n");
    while ( !done && try ) {
        if ( tws_ctlr_ready(sc) ) {
            done = 1;
            break;
        } else {
            timeout_val += 5;
            if ( timeout_val >= TWS_RESET_TIMEOUT ) {
               timeout_val = 0;
               if ( try )
                   tws_assert_soft_reset(sc);
               try--;
            }
            mtx_sleep(sc, &sc->gen_lock, 0, "tws_reinit", 5*hz);
        }
    }

    if (!done) {
        device_printf(sc->tws_dev,  "FAILED to get Controller Ready!\n");
        return;
    }

    sc->obfl_q_overrun = false;
//  device_printf(sc->tws_dev,  "Sending initConnect\n");
    if ( tws_init_connect(sc, tws_queue_depth) ) {
        TWS_TRACE_DEBUG(sc, "initConnect failed", 0, sc->is64bit);
    }
    tws_init_obfl_q(sc);

    tws_turn_on_interrupts(sc);

    wakeup_one(sc);
}