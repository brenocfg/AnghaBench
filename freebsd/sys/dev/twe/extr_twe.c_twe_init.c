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
struct twe_softc {int /*<<< orphan*/  twe_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_CONFIG_LOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_CONFIG_UNLOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_INIT_MESSAGE_CREDITS ; 
 int /*<<< orphan*/  TWE_IO_LOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_IO_UNLOCK (struct twe_softc*) ; 
 int TWE_MAX_UNITS ; 
 int /*<<< orphan*/  TWE_PARAM_FEATURES ; 
 int /*<<< orphan*/  TWE_PARAM_FEATURES_DriverShutdown ; 
 int /*<<< orphan*/  TWE_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  twe_add_unit (struct twe_softc*,int) ; 
 int /*<<< orphan*/  twe_enable_interrupts (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_init_connection (struct twe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_set_param_1 (struct twe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
twe_init(struct twe_softc *sc)
{
    int 		i;

    /*
     * Scan for drives
     */
    TWE_CONFIG_LOCK(sc);
    for (i = 0; i < TWE_MAX_UNITS; i++)
	twe_add_unit(sc, i);
    TWE_CONFIG_UNLOCK(sc);

    /*
     * Initialise connection with controller.
     */
    TWE_IO_LOCK(sc);
    twe_init_connection(sc, TWE_INIT_MESSAGE_CREDITS);

#ifdef TWE_SHUTDOWN_NOTIFICATION
    /*
     * Tell the controller we support shutdown notification.
     */
    twe_set_param_1(sc, TWE_PARAM_FEATURES, TWE_PARAM_FEATURES_DriverShutdown, 1);
#endif

    /* 
     * Mark controller up and ready to run.
     */
    sc->twe_state &= ~TWE_STATE_SHUTDOWN;

    /*
     * Finally enable interrupts.
     */
    twe_enable_interrupts(sc);
    TWE_IO_UNLOCK(sc);
}