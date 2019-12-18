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
struct port_softc {int /*<<< orphan*/ * gpio_ih; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int NPORTS ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct port_softc*,int /*<<< orphan*/ *) ; 
 struct port_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  port_intr ; 
 struct port_softc* port_sc ; 
 int /*<<< orphan*/  port_spec ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
port_attach(device_t dev)
{
	struct port_softc *sc;
	int irq;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, port_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	port_sc = sc;

	for (irq = 0; irq < NPORTS; irq ++) {
		if ((bus_setup_intr(dev, sc->res[1 + irq], INTR_TYPE_MISC,
		    port_intr, NULL, sc, &sc->gpio_ih[irq]))) {
			device_printf(dev,
			    "ERROR: Unable to register interrupt handler\n");
			return (ENXIO);
		}
	}

	return (0);
}