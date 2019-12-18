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
struct spi_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * memres; int /*<<< orphan*/  dev; int /*<<< orphan*/ * intres; int /*<<< orphan*/ * inthandle; int /*<<< orphan*/ ** cspins; int /*<<< orphan*/ * spibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pin_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int nitems (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
spi_detach(device_t dev)
{
	struct spi_softc *sc = device_get_softc(dev);
	int error, idx;

	if ((error = bus_generic_detach(sc->dev)) != 0)
		return (error);

	if (sc->spibus != NULL)
		device_delete_child(dev, sc->spibus);

	for (idx = 0; idx < nitems(sc->cspins); ++idx) {
		if (sc->cspins[idx] != NULL)
			gpio_pin_release(sc->cspins[idx]);
	}

	if (sc->inthandle != NULL)
		bus_teardown_intr(sc->dev, sc->intres, sc->inthandle);
	if (sc->intres != NULL)
		bus_release_resource(sc->dev, SYS_RES_IRQ, 0, sc->intres);
	if (sc->memres != NULL)
		bus_release_resource(sc->dev, SYS_RES_MEMORY, 0, sc->memres);

	mtx_destroy(&sc->mtx);

	return (0);
}