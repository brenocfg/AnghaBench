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
typedef  scalar_t__ uint32_t ;
struct rk_spi_softc {scalar_t__ txidx; scalar_t__ txlen; scalar_t__ fifo_size; int intreg; int /*<<< orphan*/ * txbuf; } ;

/* Variables and functions */
 int IMR_RFFIM ; 
 int IMR_TFEIM ; 
 scalar_t__ RK_SPI_READ_4 (struct rk_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_SPI_TXDR ; 
 int /*<<< orphan*/  RK_SPI_TXFLR ; 
 int /*<<< orphan*/  RK_SPI_WRITE_4 (struct rk_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rk_spi_fill_txfifo(struct rk_spi_softc *sc)
{
	uint32_t txlevel;
	txlevel = RK_SPI_READ_4(sc, RK_SPI_TXFLR);
	int cnt = 0;

	while (sc->txidx < sc->txlen && txlevel < sc->fifo_size) {
		RK_SPI_WRITE_4(sc, RK_SPI_TXDR, sc->txbuf[sc->txidx++]);
		txlevel++;
		cnt++;
	}

	if (sc->txidx != sc->txlen)
		sc->intreg |= (IMR_TFEIM  | IMR_RFFIM);
}