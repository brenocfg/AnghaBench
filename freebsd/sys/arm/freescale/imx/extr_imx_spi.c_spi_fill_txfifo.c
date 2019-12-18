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
struct spi_softc {scalar_t__ txidx; scalar_t__ txlen; scalar_t__ fifocnt; int intreg; int /*<<< orphan*/ * txbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECSPI_TXDATA ; 
 scalar_t__ FIFO_SIZE ; 
 int INTREG_TDREN ; 
 int INTREG_TEEN ; 
 int /*<<< orphan*/  WR4 (struct spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spi_fill_txfifo(struct spi_softc *sc)
{

	while (sc->txidx < sc->txlen && sc->fifocnt < FIFO_SIZE) {
		WR4(sc, ECSPI_TXDATA, sc->txbuf[sc->txidx++]);
		++sc->fifocnt;
	}

	/*
	 * If we're out of data, disable tx data ready (threshold) interrupts,
	 * and enable tx fifo empty interrupts.
	 */
	if (sc->txidx == sc->txlen)
		sc->intreg = (sc->intreg & ~INTREG_TDREN) | INTREG_TEEN;
}