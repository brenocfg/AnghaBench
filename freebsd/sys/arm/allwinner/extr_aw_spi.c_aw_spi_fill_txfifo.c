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
struct aw_spi_softc {scalar_t__ txcnt; scalar_t__ txlen; int /*<<< orphan*/ * txbuf; } ;

/* Variables and functions */
 int AW_SPI_FIFO_SIZE ; 
 int /*<<< orphan*/  AW_SPI_FSR ; 
 int AW_SPI_FSR_TF_CNT_MASK ; 
 int AW_SPI_FSR_TF_CNT_SHIFT ; 
 int AW_SPI_READ_4 (struct aw_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AW_SPI_TXD ; 
 int /*<<< orphan*/  AW_SPI_WRITE_1 (struct aw_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
aw_spi_fill_txfifo(struct aw_spi_softc *sc)
{
	uint32_t reg, txcnt;
	int i;

	if (sc->txcnt == sc->txlen)
		return;

	reg = AW_SPI_READ_4(sc, AW_SPI_FSR);
	reg &= AW_SPI_FSR_TF_CNT_MASK;
	txcnt = reg >> AW_SPI_FSR_TF_CNT_SHIFT;

	for (i = 0; i < (AW_SPI_FIFO_SIZE - txcnt); i++) {
		AW_SPI_WRITE_1(sc, AW_SPI_TXD, sc->txbuf[sc->txcnt++]);
		if (sc->txcnt == sc->txlen)
			break;
	}

	return;
}