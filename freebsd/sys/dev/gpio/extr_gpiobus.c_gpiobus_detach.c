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
struct gpiobus_softc {int sc_npins; struct gpiobus_ivar* sc_pins; int /*<<< orphan*/  sc_intr_rman; int /*<<< orphan*/  sc_mtx; } ;
struct gpiobus_ivar {struct gpiobus_ivar* name; int /*<<< orphan*/  rl; } ;
typedef  struct gpiobus_ivar device_t ;

/* Variables and functions */
 struct gpiobus_ivar* GPIOBUS_IVAR (struct gpiobus_ivar) ; 
 int /*<<< orphan*/  GPIOBUS_LOCK_DESTROY (struct gpiobus_softc*) ; 
 struct gpiobus_softc* GPIOBUS_SOFTC (struct gpiobus_ivar) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_TEMP ; 
 int bus_generic_detach (struct gpiobus_ivar) ; 
 int /*<<< orphan*/  device_delete_child (struct gpiobus_ivar,struct gpiobus_ivar) ; 
 int device_get_children (struct gpiobus_ivar,struct gpiobus_ivar**,int*) ; 
 int /*<<< orphan*/  free (struct gpiobus_ivar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_free_ivars (struct gpiobus_ivar*) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpiobus_detach(device_t dev)
{
	struct gpiobus_softc *sc;
	struct gpiobus_ivar *devi;
	device_t *devlist;
	int i, err, ndevs;

	sc = GPIOBUS_SOFTC(dev);
	KASSERT(mtx_initialized(&sc->sc_mtx),
	    ("gpiobus mutex not initialized"));
	GPIOBUS_LOCK_DESTROY(sc);

	if ((err = bus_generic_detach(dev)) != 0)
		return (err);

	if ((err = device_get_children(dev, &devlist, &ndevs)) != 0)
		return (err);
	for (i = 0; i < ndevs; i++) {
		devi = GPIOBUS_IVAR(devlist[i]);
		gpiobus_free_ivars(devi);
		resource_list_free(&devi->rl);
		free(devi, M_DEVBUF);
		device_delete_child(dev, devlist[i]);
	}
	free(devlist, M_TEMP);
	rman_fini(&sc->sc_intr_rman);
	if (sc->sc_pins) {
		for (i = 0; i < sc->sc_npins; i++) {
			if (sc->sc_pins[i].name != NULL)
				free(sc->sc_pins[i].name, M_DEVBUF);
			sc->sc_pins[i].name = NULL;
		}
		free(sc->sc_pins, M_DEVBUF);
		sc->sc_pins = NULL;
	}

	return (0);
}