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
struct twe_softc {int twe_state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TWE_IO_LOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_IO_UNLOCK (struct twe_softc*) ; 
 int TWE_STATE_DETACHING ; 
 int TWE_STATE_OPEN ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct twe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_free (struct twe_softc*) ; 
 scalar_t__ twe_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
twe_detach(device_t dev)
{
    struct twe_softc	*sc = device_get_softc(dev);

    debug_called(4);

    TWE_IO_LOCK(sc);
    if (sc->twe_state & TWE_STATE_OPEN) {
	TWE_IO_UNLOCK(sc);
	return (EBUSY);
    }
    sc->twe_state |= TWE_STATE_DETACHING;
    TWE_IO_UNLOCK(sc);

    /*	
     * Shut the controller down.
     */
    if (twe_shutdown(dev)) {
	TWE_IO_LOCK(sc);
	sc->twe_state &= ~TWE_STATE_DETACHING;
	TWE_IO_UNLOCK(sc);
	return (EBUSY);
    }

    twe_free(sc);

    return(0);
}