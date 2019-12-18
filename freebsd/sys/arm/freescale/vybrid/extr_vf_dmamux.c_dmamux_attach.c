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
struct dmamux_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/ * bsh; int /*<<< orphan*/ * bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dmamux_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct dmamux_softc* dmamux_sc ; 
 int /*<<< orphan*/  dmamux_spec ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmamux_attach(device_t dev)
{
	struct dmamux_softc *sc;
	int i;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, dmamux_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	for (i = 0; i < 4; i++) {
		sc->bst[i] = rman_get_bustag(sc->res[i]);
		sc->bsh[i] = rman_get_bushandle(sc->res[i]);
	}

	dmamux_sc = sc;

	return (0);
}