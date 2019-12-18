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
struct jz4780_clock_softc {int /*<<< orphan*/  res; int /*<<< orphan*/ * clkdom; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_LOCK_DESTROY (struct jz4780_clock_softc*) ; 
 int /*<<< orphan*/  CGU_LOCK_INIT (struct jz4780_clock_softc*) ; 
 int ENXIO ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clkdom_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdom_dump (int /*<<< orphan*/ *) ; 
 scalar_t__ clkdom_finit (int /*<<< orphan*/ *) ; 
 struct jz4780_clock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jz4780_clock_fixup (struct jz4780_clock_softc*) ; 
 scalar_t__ jz4780_clock_register (struct jz4780_clock_softc*) ; 
 int /*<<< orphan*/  jz4780_clock_spec ; 

__attribute__((used)) static int
jz4780_clock_attach(device_t dev)
{
	struct jz4780_clock_softc *sc;

	sc = device_get_softc(dev);
	if (bus_alloc_resources(dev, jz4780_clock_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	sc->dev = dev;
	CGU_LOCK_INIT(sc);

	sc->clkdom = clkdom_create(dev);
	if (sc->clkdom == NULL)
		goto fail;
	if (jz4780_clock_register(sc) != 0)
		goto fail;
	if (clkdom_finit(sc->clkdom) != 0)
		goto fail;
	if (jz4780_clock_fixup(sc) != 0)
		goto fail;
	if (bootverbose)
		clkdom_dump(sc->clkdom);

	return (0);
fail:
	bus_release_resources(dev, jz4780_clock_spec, sc->res);
	CGU_LOCK_DESTROY(sc);

	return (ENXIO);
}