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
 int /*<<< orphan*/  MTK_SPIDATA ; 
 int /*<<< orphan*/  MTK_SPIMOREBUF ; 
 int /*<<< orphan*/  MTK_SPIOPCODE ; 
 int /*<<< orphan*/  MTK_SPITRANS ; 
 int MTK_SPI_READ ; 
 int MTK_SPI_WRITE ; 
 int /*<<< orphan*/  SPISTART ; 
 int SPI_READ (struct mtk_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_SET_BITS (struct mtk_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_WRITE (struct mtk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mtk_spi_wait (struct mtk_spi_softc*) ; 

__attribute__((used)) static uint8_t
mtk_spi_txrx(struct mtk_spi_softc *sc, uint8_t *data, int write)
{

	if (mtk_spi_wait(sc))
		return (0xff);

	if (write == MTK_SPI_WRITE) {
		SPI_WRITE(sc, MTK_SPIOPCODE, (*data));
		SPI_WRITE(sc, MTK_SPIMOREBUF, (8<<24));
	} else {
		SPI_WRITE(sc, MTK_SPIMOREBUF, (8<<12));
	}

	SPI_SET_BITS(sc, MTK_SPITRANS, SPISTART);

	if (mtk_spi_wait(sc))
		return (0xff);

	if (write == MTK_SPI_READ) {
		*data = SPI_READ(sc, MTK_SPIDATA) & 0xff;
	}

	return (0);
}