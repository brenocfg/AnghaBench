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
struct aw_spi_softc {int /*<<< orphan*/  spibus; int /*<<< orphan*/  clk_mod; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  rst_ahb; int /*<<< orphan*/ * res; int /*<<< orphan*/  intrhand; int /*<<< orphan*/  mtx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  aw_spi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_spi_intr ; 
 int /*<<< orphan*/  aw_spi_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct aw_spi_softc*,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct aw_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_spi_attach(device_t dev)
{
	struct aw_spi_softc *sc;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	mtx_init(&sc->mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	if (bus_alloc_resources(dev, aw_spi_spec, sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		error = ENXIO;
		goto fail;
	}

	if (bus_setup_intr(dev, sc->res[1],
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, aw_spi_intr, sc,
	    &sc->intrhand)) {
		bus_release_resources(dev, aw_spi_spec, sc->res);
		device_printf(dev, "cannot setup interrupt handler\n");
		return (ENXIO);
	}

	/* De-assert reset */
	if (hwreset_get_by_ofw_idx(dev, 0, 0, &sc->rst_ahb) == 0) {
		error = hwreset_deassert(sc->rst_ahb);
		if (error != 0) {
			device_printf(dev, "cannot de-assert reset\n");
			goto fail;
		}
	}

	/* Activate the module clock. */
	error = clk_get_by_ofw_name(dev, 0, "ahb", &sc->clk_ahb);
	if (error != 0) {
		device_printf(dev, "cannot get ahb clock\n");
		goto fail;
	}
	error = clk_get_by_ofw_name(dev, 0, "mod", &sc->clk_mod);
	if (error != 0) {
		device_printf(dev, "cannot get mod clock\n");
		goto fail;
	}
	error = clk_enable(sc->clk_ahb);
	if (error != 0) {
		device_printf(dev, "cannot enable ahb clock\n");
		goto fail;
	}
	error = clk_enable(sc->clk_mod);
	if (error != 0) {
		device_printf(dev, "cannot enable mod clock\n");
		goto fail;
	}

	sc->spibus = device_add_child(dev, "spibus", -1);

	return (0);

fail:
	aw_spi_detach(dev);
	return (error);
}