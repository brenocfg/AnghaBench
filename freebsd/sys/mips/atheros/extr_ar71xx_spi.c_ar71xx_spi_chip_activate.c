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
typedef  int uint32_t ;
struct ar71xx_spi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_SPI_IO_CTRL ; 
 int /*<<< orphan*/  SPI_BARRIER_WRITE (struct ar71xx_spi_softc*) ; 
 int SPI_IO_CTRL_CS0 ; 
 int SPI_IO_CTRL_CSMASK ; 
 int /*<<< orphan*/  SPI_WRITE (struct ar71xx_spi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar71xx_spi_chip_activate(struct ar71xx_spi_softc *sc, int cs)
{
	uint32_t ioctrl = SPI_IO_CTRL_CSMASK;
	/*
	 * Put respective CSx to low
	 */
	ioctrl &= ~(SPI_IO_CTRL_CS0 << cs);

	/*
	 * Make sure any other writes have gone out to the
	 * device before changing the chip select line;
	 * then ensure that it has made it out to the device
	 * before continuing.
	 */
	SPI_BARRIER_WRITE(sc);
	SPI_WRITE(sc, AR71XX_SPI_IO_CTRL, ioctrl);
	SPI_BARRIER_WRITE(sc);
}