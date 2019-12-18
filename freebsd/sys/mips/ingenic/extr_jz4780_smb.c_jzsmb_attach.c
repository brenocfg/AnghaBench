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
struct jzsmb_softc {scalar_t__ bus_freq; int i2c_freq; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * clk; int /*<<< orphan*/  res; int /*<<< orphan*/ * iicbus; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ *) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int clk_get_freq (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct jzsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jzsmb_spec ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jzsmb_attach(device_t dev)
{
	struct jzsmb_softc *sc;
	phandle_t node;
	int error;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);
	mtx_init(&sc->mtx, device_get_nameunit(dev), "jzsmb", MTX_DEF);

	error = clk_get_by_ofw_index(dev, 0, 0, &sc->clk);
	if (error != 0) {
		device_printf(dev, "cannot get clock\n");
		goto fail;
	}
	error = clk_enable(sc->clk);
	if (error != 0) {
		device_printf(dev, "cannot enable clock\n");
		goto fail;
	}
	error = clk_get_freq(sc->clk, &sc->bus_freq);
	if (error != 0 || sc->bus_freq == 0) {
		device_printf(dev, "cannot get bus frequency\n");
		return (error);
	}

	if (bus_alloc_resources(dev, jzsmb_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		error = ENXIO;
		goto fail;
	}

	if (OF_getencprop(node, "clock-frequency", &sc->i2c_freq,
	    sizeof(sc->i2c_freq)) != 0 || sc->i2c_freq == 0)
		sc->i2c_freq = 100000;	/* Default to standard mode */

	sc->iicbus = device_add_child(dev, "iicbus", -1);
	if (sc->iicbus == NULL) {
		device_printf(dev, "cannot add iicbus child device\n");
		error = ENXIO;
		goto fail;
	}

	bus_generic_attach(dev);

	return (0);

fail:
	bus_release_resources(dev, jzsmb_spec, &sc->res);
	if (sc->clk != NULL)
		clk_release(sc->clk);
	mtx_destroy(&sc->mtx);
	return (error);
}