#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct twe_softc {int twe_wait_aen; struct twe_request** twe_lookup; int /*<<< orphan*/  twe_host_id; } ;
struct twe_request {int dummy; } ;
struct TYPE_4__ {int request_id; int /*<<< orphan*/  host_id; } ;
struct TYPE_5__ {TYPE_1__ generic; } ;
typedef  TYPE_2__ TWE_Command ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 TYPE_2__* TWE_FIND_COMMAND (struct twe_request*) ; 
 int /*<<< orphan*/  TWE_IO_LOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_IO_UNLOCK (struct twe_softc*) ; 
 int TWE_MAX_RESET_TRIES ; 
 int TWE_Q_LENGTH ; 
 int /*<<< orphan*/  TWE_STATUS (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_STATUS_MICROCONTROLLER_READY ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct twe_request* twe_allocate_request (struct twe_softc*,int) ; 
 int /*<<< orphan*/  twe_check_bits (struct twe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_disable_interrupts (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_initq_bio (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_initq_busy (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_initq_complete (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_initq_free (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_initq_ready (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_printf (struct twe_softc*,char*,...) ; 
 int /*<<< orphan*/  twe_release_request (struct twe_request*) ; 
 int /*<<< orphan*/  twe_soft_reset (struct twe_softc*) ; 
 scalar_t__ twe_wait_status (struct twe_softc*,int /*<<< orphan*/ ,int) ; 

int
twe_setup(struct twe_softc *sc)
{
    struct twe_request	*tr;
    TWE_Command		*cmd;
    u_int32_t		status_reg;
    int			i;

    debug_called(4);

    /*
     * Initialise request queues.
     */
    twe_initq_free(sc);
    twe_initq_bio(sc);
    twe_initq_ready(sc);
    twe_initq_busy(sc);
    twe_initq_complete(sc);
    sc->twe_wait_aen = -1;

    /*
     * Allocate request structures up front.
     */
    for (i = 0; i < TWE_Q_LENGTH; i++) {
	if ((tr = twe_allocate_request(sc, i)) == NULL)
	    return(ENOMEM);
	/*
	 * Set global defaults that won't change.
	 */
	cmd = TWE_FIND_COMMAND(tr);
	cmd->generic.host_id = sc->twe_host_id;		/* controller-assigned host ID */
	cmd->generic.request_id = i;			/* our index number */
	sc->twe_lookup[i] = tr;

	/*
	 * Put command onto the freelist.
	 */
	TWE_IO_LOCK(sc);
	twe_release_request(tr);
	TWE_IO_UNLOCK(sc);
    }
    TWE_IO_LOCK(sc);

    /*
     * Check status register for errors, clear them.
     */
    status_reg = TWE_STATUS(sc);
    twe_check_bits(sc, status_reg);

    /*
     * Wait for the controller to come ready.
     */
    if (twe_wait_status(sc, TWE_STATUS_MICROCONTROLLER_READY, 60)) {
	TWE_IO_UNLOCK(sc);
	twe_printf(sc, "microcontroller not ready\n");
	return(ENXIO);
    }

    /*
     * Disable interrupts from the card.
     */
    twe_disable_interrupts(sc);

    /*
     * Soft reset the controller, look for the AEN acknowledging the reset,
     * check for errors, drain the response queue.
     */
    for (i = 0; i < TWE_MAX_RESET_TRIES; i++) {

	if (i > 0)
	    twe_printf(sc, "reset %d failed, trying again\n", i);
	
	if (!twe_soft_reset(sc))
	    break;			/* reset process complete */
    }
    TWE_IO_UNLOCK(sc);
    /* did we give up? */
    if (i >= TWE_MAX_RESET_TRIES) {
	twe_printf(sc, "can't initialise controller, giving up\n");
	return(ENXIO);
    }

    return(0);
}