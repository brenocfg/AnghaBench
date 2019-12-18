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
struct rk_spi_softc {int fifo_size; int /*<<< orphan*/  spibus; int /*<<< orphan*/  max_freq; int /*<<< orphan*/  clk_spi; int /*<<< orphan*/  clk_apb; int /*<<< orphan*/ * res; int /*<<< orphan*/  intrhand; int /*<<< orphan*/  mtx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RK_SPI_IMR ; 
 int /*<<< orphan*/  RK_SPI_RXFTLR ; 
 int /*<<< orphan*/  RK_SPI_TXFTLR ; 
 int /*<<< orphan*/  RK_SPI_WRITE_4 (struct rk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rk_spi_softc*,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct rk_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_spi_detach (int /*<<< orphan*/ ) ; 
 int rk_spi_fifo_size (struct rk_spi_softc*) ; 
 int /*<<< orphan*/  rk_spi_intr ; 
 int /*<<< orphan*/  rk_spi_spec ; 

__attribute__((used)) static int
rk_spi_attach(device_t dev)
{
	struct rk_spi_softc *sc;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	mtx_init(&sc->mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	if (bus_alloc_resources(dev, rk_spi_spec, sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		error = ENXIO;
		goto fail;
	}

	if (bus_setup_intr(dev, sc->res[1],
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, rk_spi_intr, sc,
	    &sc->intrhand)) {
		bus_release_resources(dev, rk_spi_spec, sc->res);
		device_printf(dev, "cannot setup interrupt handler\n");
		return (ENXIO);
	}

	/* Activate the module clock. */
	error = clk_get_by_ofw_name(dev, 0, "apb_pclk", &sc->clk_apb);
	if (error != 0) {
		device_printf(dev, "cannot get apb_pclk clock\n");
		goto fail;
	}
	error = clk_get_by_ofw_name(dev, 0, "spiclk", &sc->clk_spi);
	if (error != 0) {
		device_printf(dev, "cannot get spiclk clock\n");
		goto fail;
	}
	error = clk_enable(sc->clk_apb);
	if (error != 0) {
		device_printf(dev, "cannot enable ahb clock\n");
		goto fail;
	}
	error = clk_enable(sc->clk_spi);
	if (error != 0) {
		device_printf(dev, "cannot enable spiclk clock\n");
		goto fail;
	}
	clk_get_freq(sc->clk_spi, &sc->max_freq);

	sc->fifo_size = rk_spi_fifo_size(sc);
	if (sc->fifo_size == 0) {
		device_printf(dev, "failed to get fifo size\n");
		goto fail;
	}

	sc->spibus = device_add_child(dev, "spibus", -1);

	RK_SPI_WRITE_4(sc, RK_SPI_IMR, 0);
	RK_SPI_WRITE_4(sc, RK_SPI_TXFTLR, sc->fifo_size/2 - 1);
	RK_SPI_WRITE_4(sc, RK_SPI_RXFTLR, sc->fifo_size/2 - 1);

	return (bus_generic_attach(dev));

fail:
	rk_spi_detach(dev);
	return (error);
}