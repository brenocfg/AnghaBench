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
struct gpiobus_softc {int /*<<< orphan*/ * sc_owner; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOBUS_ASSERT_UNLOCKED (struct gpiobus_softc*) ; 
 int /*<<< orphan*/  GPIOBUS_LOCK (struct gpiobus_softc*) ; 
 int /*<<< orphan*/  GPIOBUS_UNLOCK (struct gpiobus_softc*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct gpiobus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wakeup (struct gpiobus_softc*) ; 

__attribute__((used)) static void
gpiobus_release_bus(device_t busdev, device_t child)
{
	struct gpiobus_softc *sc;

	sc = device_get_softc(busdev);
	GPIOBUS_ASSERT_UNLOCKED(sc);
	GPIOBUS_LOCK(sc);
	if (sc->sc_owner == NULL)
		panic("%s: %s releasing unowned bus.",
		    device_get_nameunit(busdev),
		    device_get_nameunit(child));
	if (sc->sc_owner != child)
		panic("%s: %s trying to release bus owned by %s",
		    device_get_nameunit(busdev),
		    device_get_nameunit(child),
		    device_get_nameunit(sc->sc_owner));
	sc->sc_owner = NULL;
	wakeup(sc);
	GPIOBUS_UNLOCK(sc);
}