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
struct gpiobus_softc {int /*<<< orphan*/ * sc_owner; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  GPIOBUS_ASSERT_UNLOCKED (struct gpiobus_softc*) ; 
 int GPIOBUS_DONTWAIT ; 
 int /*<<< orphan*/  GPIOBUS_LOCK (struct gpiobus_softc*) ; 
 int /*<<< orphan*/  GPIOBUS_UNLOCK (struct gpiobus_softc*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct gpiobus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (struct gpiobus_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiobus_acquire_bus(device_t busdev, device_t child, int how)
{
	struct gpiobus_softc *sc;

	sc = device_get_softc(busdev);
	GPIOBUS_ASSERT_UNLOCKED(sc);
	GPIOBUS_LOCK(sc);
	if (sc->sc_owner != NULL) {
		if (sc->sc_owner == child)
			panic("%s: %s still owns the bus.",
			    device_get_nameunit(busdev),
			    device_get_nameunit(child));
		if (how == GPIOBUS_DONTWAIT) {
			GPIOBUS_UNLOCK(sc);
			return (EWOULDBLOCK);
		}
		while (sc->sc_owner != NULL)
			mtx_sleep(sc, &sc->sc_mtx, 0, "gpiobuswait", 0);
	}
	sc->sc_owner = child;
	GPIOBUS_UNLOCK(sc);

	return (0);
}