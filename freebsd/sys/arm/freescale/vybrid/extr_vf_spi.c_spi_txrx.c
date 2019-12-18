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
typedef  int uint32_t ;
struct spi_softc {int dummy; } ;

/* Variables and functions */
 int PUSHR_CONT ; 
 int PUSHR_CTCNT ; 
 int PUSHR_EOQ ; 
 int PUSHR_PCS_S ; 
 int READ1 (struct spi_softc*,int /*<<< orphan*/ ) ; 
 int READ4 (struct spi_softc*,int /*<<< orphan*/ ) ; 
 int SPI_FIFO_SIZE ; 
 int /*<<< orphan*/  SPI_POPR ; 
 int /*<<< orphan*/  SPI_PUSHR ; 
 int /*<<< orphan*/  SPI_SR ; 
 int SR_EOQF ; 
 int SR_RFDF ; 
 int SR_TCF ; 
 int /*<<< orphan*/  WRITE4 (struct spi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
spi_txrx(struct spi_softc *sc, uint8_t *out_buf,
    uint8_t *in_buf, int bufsz, int cs)
{
	uint32_t reg, wreg;
	uint32_t txcnt;
	uint32_t i;

	txcnt = 0;

	for (i = 0; i < bufsz; i++) {
		txcnt++;
		wreg = out_buf[i];
		wreg |= PUSHR_CONT;
		wreg |= (cs << PUSHR_PCS_S);
		if (i == 0)
			wreg |= PUSHR_CTCNT;
		if (i == (bufsz - 1) || txcnt == SPI_FIFO_SIZE)
			wreg |= PUSHR_EOQ;
		WRITE4(sc, SPI_PUSHR, wreg);

		if (i == (bufsz - 1) || txcnt == SPI_FIFO_SIZE) {
			txcnt = 0;

			/* Wait last entry in a queue to be transmitted */
			while((READ4(sc, SPI_SR) & SR_EOQF) == 0)
				continue;

			reg = READ4(sc, SPI_SR);
			reg |= (SR_TCF | SR_EOQF);
			WRITE4(sc, SPI_SR, reg);
		}

		/* Wait until RX FIFO is empty */
		while((READ4(sc, SPI_SR) & SR_RFDF) == 0)
			continue;

		in_buf[i] = READ1(sc, SPI_POPR);
	}

	return (0);
}