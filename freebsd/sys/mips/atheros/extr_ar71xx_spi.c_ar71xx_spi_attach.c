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
struct ar71xx_spi_softc {int /*<<< orphan*/  sc_reg_ctrl; int /*<<< orphan*/  sc_mem_res; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_SPI_CTRL ; 
 int /*<<< orphan*/  AR71XX_SPI_FS ; 
 int /*<<< orphan*/  AR71XX_SPI_IO_CTRL ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SPI_BARRIER_WRITE (struct ar71xx_spi_softc*) ; 
 int SPI_IO_CTRL_CSMASK ; 
 int /*<<< orphan*/  SPI_READ (struct ar71xx_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_WRITE (struct ar71xx_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct ar71xx_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ar71xx_spi_attach(device_t dev)
{
	struct ar71xx_spi_softc *sc = device_get_softc(dev);
	int rid;

	sc->sc_dev = dev;
        rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, 
	    RF_ACTIVE);
	if (!sc->sc_mem_res) {
		device_printf(dev, "Could not map memory\n");
		return (ENXIO);
	}

	SPI_WRITE(sc, AR71XX_SPI_FS, 1);

	/* Flush out read before reading the control register */
	SPI_BARRIER_WRITE(sc);

	sc->sc_reg_ctrl  = SPI_READ(sc, AR71XX_SPI_CTRL);

	/*
	 * XXX TODO: document what the SPI control register does.
	 */
	SPI_WRITE(sc, AR71XX_SPI_CTRL, 0x43);

	/*
	 * Ensure the config register write has gone out before configuring
	 * the chip select mask.
	 */
	SPI_BARRIER_WRITE(sc);
	SPI_WRITE(sc, AR71XX_SPI_IO_CTRL, SPI_IO_CTRL_CSMASK);

	/*
	 * .. and ensure the write has gone out before continuing.
	 */
	SPI_BARRIER_WRITE(sc);

	device_add_child(dev, "spibus", -1);
	return (bus_generic_attach(dev));
}