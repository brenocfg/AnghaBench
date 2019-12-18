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
struct ar71xx_spi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_SPI_IO_CTRL ; 
 int /*<<< orphan*/  SPI_IO_CTRL_CSMASK ; 
 int /*<<< orphan*/  SPI_WRITE (struct ar71xx_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar71xx_spi_chip_deactivate(struct ar71xx_spi_softc *sc, int cs)
{
	/*
	 * Put all CSx to high
	 */
	SPI_WRITE(sc, AR71XX_SPI_IO_CTRL, SPI_IO_CTRL_CSMASK);
}