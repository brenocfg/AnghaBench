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
struct twsi_softc {int /*<<< orphan*/ * iicbus; int /*<<< orphan*/  res; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_oneshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct twsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_spec ; 
 int /*<<< orphan*/  twsi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twsi_intr_start ; 

int
twsi_attach(device_t dev)
{
	struct twsi_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	mtx_init(&sc->mutex, device_get_nameunit(dev), "twsi", MTX_DEF);

	if (bus_alloc_resources(dev, res_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		twsi_detach(dev);
		return (ENXIO);
	}

	/* Attach the iicbus. */
	if ((sc->iicbus = device_add_child(dev, "iicbus", -1)) == NULL) {
		device_printf(dev, "could not allocate iicbus instance\n");
		twsi_detach(dev);
		return (ENXIO);
	}
	bus_generic_attach(dev);

	config_intrhook_oneshot(twsi_intr_start, dev);

	return (0);
}