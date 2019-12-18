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
typedef  int uint8_t ;
struct mtk_spi_softc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MTK_SPICTL ; 
 int /*<<< orphan*/  MTK_SPIDATA ; 
 int MTK_SPI_WRITE ; 
 int SPI_READ (struct mtk_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_SET_BITS (struct mtk_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_WRITE (struct mtk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  START_READ ; 
 int /*<<< orphan*/  START_WRITE ; 
 scalar_t__ mtk_spi_wait (struct mtk_spi_softc*) ; 

__attribute__((used)) static uint8_t
mtk_spi_txrx(struct mtk_spi_softc *sc, uint8_t *data, int write)
{

	if (mtk_spi_wait(sc))
		return (EBUSY);

	if (write == MTK_SPI_WRITE) {
		SPI_WRITE(sc, MTK_SPIDATA, *data);
		SPI_SET_BITS(sc, MTK_SPICTL, START_WRITE);
	} else {/* MTK_SPI_READ */
		SPI_SET_BITS(sc, MTK_SPICTL, START_READ);
		if (mtk_spi_wait(sc))
			return (EBUSY);

		*data = SPI_READ(sc, MTK_SPIDATA) & 0xff;
	}
	return (0);
}