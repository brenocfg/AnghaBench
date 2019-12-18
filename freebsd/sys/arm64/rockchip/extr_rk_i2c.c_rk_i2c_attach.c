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
struct rk_i2c_softc {int /*<<< orphan*/ * iicbus; int /*<<< orphan*/ * sclk; int /*<<< orphan*/ * pclk; int /*<<< orphan*/ * res; int /*<<< orphan*/  intrhand; int /*<<< orphan*/  mtx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rk_i2c_softc*,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ *) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  clk_set_assigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct rk_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ rk_i2c_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_i2c_intr ; 
 int /*<<< orphan*/  rk_i2c_spec ; 

__attribute__((used)) static int
rk_i2c_attach(device_t dev)
{
	struct rk_i2c_softc *sc;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	mtx_init(&sc->mtx, device_get_nameunit(dev), "rk_i2c", MTX_DEF);

	if (bus_alloc_resources(dev, rk_i2c_spec, sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		error = ENXIO;
		goto fail;
	}

	if (bus_setup_intr(dev, sc->res[1],
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, rk_i2c_intr, sc,
	    &sc->intrhand)) {
		bus_release_resources(dev, rk_i2c_spec, sc->res);
		device_printf(dev, "cannot setup interrupt handler\n");
		return (ENXIO);
	}

	clk_set_assigned(dev, ofw_bus_get_node(dev));

	/* Activate the module clocks. */
	error = clk_get_by_ofw_name(dev, 0, "i2c", &sc->sclk);
	if (error != 0) {
		device_printf(dev, "cannot get i2c clock\n");
		goto fail;
	}
	error = clk_enable(sc->sclk);
	if (error != 0) {
		device_printf(dev, "cannot enable i2c clock\n");
		goto fail;
	}
	/* pclk clock is optional. */
	error = clk_get_by_ofw_name(dev, 0, "pclk", &sc->pclk);
	if (error != 0 && error != ENOENT) {
		device_printf(dev, "cannot get pclk clock\n");
		goto fail;
	}
	if (sc->sclk != NULL) {
		error = clk_enable(sc->sclk);
		if (error != 0) {
			device_printf(dev, "cannot enable pclk clock\n");
			goto fail;
		}
	}

	sc->iicbus = device_add_child(dev, "iicbus", -1);
	if (sc->iicbus == NULL) {
		device_printf(dev, "cannot add iicbus child device\n");
		error = ENXIO;
		goto fail;
	}

	bus_generic_attach(dev);

	return (0);

fail:
	if (rk_i2c_detach(dev) != 0)
		device_printf(dev, "Failed to detach\n");
	return (error);
}