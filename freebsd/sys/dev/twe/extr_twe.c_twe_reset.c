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
struct twe_softc {int /*<<< orphan*/  twe_io_lock; } ;
struct twe_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIBIO ; 
 int TWE_MAX_RESET_TRIES ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_sleep (struct twe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct twe_request* twe_dequeue_busy (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_disable_interrupts (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_enable_interrupts (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_enqueue_ready (struct twe_request*) ; 
 int /*<<< orphan*/  twe_printf (struct twe_softc*,char*,...) ; 
 int /*<<< orphan*/  twe_soft_reset (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_startio (struct twe_softc*) ; 

__attribute__((used)) static void
twe_reset(struct twe_softc *sc)
{
    struct twe_request	*tr;
    int			i;

    /*
     * Sleep for a short period to allow AENs to be signalled.
     */
    mtx_sleep(sc, &sc->twe_io_lock, PRIBIO, "twereset", hz);

    /*
     * Disable interrupts from the controller, and mask any accidental entry
     * into our interrupt handler.
     */
    twe_printf(sc, "controller reset in progress...\n");
    twe_disable_interrupts(sc);

    /*
     * Try to soft-reset the controller.
     */
    for (i = 0; i < TWE_MAX_RESET_TRIES; i++) {

	if (i > 0)
	    twe_printf(sc, "reset %d failed, trying again\n", i);
	
	if (!twe_soft_reset(sc))
	    break;			/* reset process complete */
    }
    /* did we give up? */
    if (i >= TWE_MAX_RESET_TRIES) {
	twe_printf(sc, "can't reset controller, giving up\n");
	goto out;
    }

    /*
     * Move all of the commands that were busy back to the ready queue.
     */
    i = 0;
    while ((tr = twe_dequeue_busy(sc)) != NULL) {
	twe_enqueue_ready(tr);
	i++;
    }

    /*
     * Kick the controller to start things going again, then re-enable interrupts.
     */
    twe_startio(sc);
    twe_printf(sc, "controller reset done, %d commands restarted\n", i);

out:
    twe_enable_interrupts(sc);
}