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
 int /*<<< orphan*/  TWE_IO_ASSERT_LOCKED (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_SHUTDOWN_MESSAGE_CREDITS ; 
 int /*<<< orphan*/  TWE_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  twe_disable_interrupts (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_init_connection (struct twe_softc*,int /*<<< orphan*/ ) ; 

void
twe_deinit(struct twe_softc *sc)
{
    /*
     * Mark the controller as shutting down, and disable any further interrupts.
     */
    TWE_IO_ASSERT_LOCKED(sc);
    sc->twe_state |= TWE_STATE_SHUTDOWN;
    twe_disable_interrupts(sc);

#ifdef TWE_SHUTDOWN_NOTIFICATION
    /*
     * Disconnect from the controller
     */
    twe_init_connection(sc, TWE_SHUTDOWN_MESSAGE_CREDITS);
#endif
}