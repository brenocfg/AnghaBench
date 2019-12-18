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
struct combiner_softc {int /*<<< orphan*/ * ih; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int NGRP ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct combiner_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  combiner_intr ; 
 struct combiner_softc* combiner_sc ; 
 int /*<<< orphan*/  combiner_spec ; 
 struct combiner_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
combiner_attach(device_t dev)
{
	struct combiner_softc *sc;
	int err;
	int i;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, combiner_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	combiner_sc = sc;

        /* Setup interrupt handler */
	for (i = 0; i < NGRP; i++) {
		err = bus_setup_intr(dev, sc->res[1+i], INTR_TYPE_BIO | \
		    INTR_MPSAFE, NULL, combiner_intr, sc, &sc->ih[i]);
		if (err) {
			device_printf(dev, "Unable to alloc int resource.\n");
			return (ENXIO);
		}
	}

	return (0);
}