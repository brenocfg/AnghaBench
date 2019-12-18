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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct aw_spi_softc {scalar_t__ rxcnt; scalar_t__ rxlen; int /*<<< orphan*/ * rxbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  AW_SPI_FSR ; 
 int AW_SPI_FSR_RF_CNT_MASK ; 
 int AW_SPI_FSR_RF_CNT_SHIFT ; 
 int /*<<< orphan*/  AW_SPI_RDX ; 
 int /*<<< orphan*/  AW_SPI_READ_1 (struct aw_spi_softc*,int /*<<< orphan*/ ) ; 
 int AW_SPI_READ_4 (struct aw_spi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
aw_spi_read_rxfifo(struct aw_spi_softc *sc)
{
	uint32_t reg;
	uint8_t val;
	int i;

	if (sc->rxcnt == sc->rxlen)
		return;

	reg = AW_SPI_READ_4(sc, AW_SPI_FSR);
	reg = (reg & AW_SPI_FSR_RF_CNT_MASK) >> AW_SPI_FSR_RF_CNT_SHIFT;

	for (i = 0; i < reg; i++) {
		val = AW_SPI_READ_1(sc, AW_SPI_RDX);
		if (sc->rxcnt < sc->rxlen)
			sc->rxbuf[sc->rxcnt++] = val;
	}
}