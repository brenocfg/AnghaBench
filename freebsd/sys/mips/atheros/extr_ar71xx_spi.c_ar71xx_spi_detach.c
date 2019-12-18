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
struct ar71xx_spi_softc {scalar_t__ sc_mem_res; int /*<<< orphan*/  sc_reg_ctrl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_SPI_CTRL ; 
 int /*<<< orphan*/  AR71XX_SPI_FS ; 
 int /*<<< orphan*/  SPI_BARRIER_WRITE (struct ar71xx_spi_softc*) ; 
 int /*<<< orphan*/  SPI_WRITE (struct ar71xx_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ar71xx_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar71xx_spi_detach(device_t dev)
{
	struct ar71xx_spi_softc *sc = device_get_softc(dev);

	/*
	 * Ensure any other writes to the device are finished
	 * before we tear down the SPI device.
	 */
	SPI_BARRIER_WRITE(sc);

	/*
	 * Restore the control register; ensure it has hit the
	 * hardware before continuing.
	 */
	SPI_WRITE(sc, AR71XX_SPI_CTRL, sc->sc_reg_ctrl);
	SPI_BARRIER_WRITE(sc);

	/*
	 * And now, put the flash back into mapped IO mode and
	 * ensure _that_ has completed before we finish up.
	 */
	SPI_WRITE(sc, AR71XX_SPI_FS, 0);
	SPI_BARRIER_WRITE(sc);

	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);

	return (0);
}