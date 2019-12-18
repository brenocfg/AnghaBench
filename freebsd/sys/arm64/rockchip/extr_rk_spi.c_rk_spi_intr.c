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
struct rk_spi_softc {scalar_t__ txidx; scalar_t__ txlen; int intreg; } ;

/* Variables and functions */
 int ISR_RFFIS ; 
 int ISR_TFEIS ; 
 int /*<<< orphan*/  RK_SPI_ICR ; 
 int /*<<< orphan*/  RK_SPI_IMR ; 
 int /*<<< orphan*/  RK_SPI_ISR ; 
 int /*<<< orphan*/  RK_SPI_LOCK (struct rk_spi_softc*) ; 
 int RK_SPI_READ_4 (struct rk_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_SPI_UNLOCK (struct rk_spi_softc*) ; 
 int /*<<< orphan*/  RK_SPI_WRITE_4 (struct rk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk_spi_empty_rxfifo (struct rk_spi_softc*) ; 
 int /*<<< orphan*/  rk_spi_fill_txfifo (struct rk_spi_softc*) ; 
 int /*<<< orphan*/  wakeup (struct rk_spi_softc*) ; 

__attribute__((used)) static void
rk_spi_intr(void *arg)
{
	struct rk_spi_softc *sc;
	uint32_t intreg, isr;

	sc = arg;

	RK_SPI_LOCK(sc);
	intreg = RK_SPI_READ_4(sc, RK_SPI_IMR);
	isr = RK_SPI_READ_4(sc, RK_SPI_ISR);
	RK_SPI_WRITE_4(sc, RK_SPI_ICR, isr);

	if (isr & ISR_RFFIS)
		rk_spi_empty_rxfifo(sc);

	if (isr & ISR_TFEIS)
		rk_spi_fill_txfifo(sc);

	/* no bytes left, disable interrupt */
	if (sc->txidx == sc->txlen) {
		sc->intreg = 0;
		wakeup(sc);
	}

	if (sc->intreg != intreg) {
		(void)RK_SPI_WRITE_4(sc, RK_SPI_IMR, sc->intreg);
		(void)RK_SPI_READ_4(sc, RK_SPI_IMR);
	}

	RK_SPI_UNLOCK(sc);
}