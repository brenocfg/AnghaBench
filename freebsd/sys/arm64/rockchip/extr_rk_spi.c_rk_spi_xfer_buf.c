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
struct rk_spi_softc {scalar_t__ rxlen; scalar_t__ rxidx; scalar_t__ txlen; scalar_t__ txidx; scalar_t__ intreg; int /*<<< orphan*/  mtx; void* txbuf; void* rxbuf; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RK_SPI_IMR ; 
 int /*<<< orphan*/  RK_SPI_WRITE_4 (struct rk_spi_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int hz ; 
 int msleep (struct rk_spi_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rk_spi_empty_rxfifo (struct rk_spi_softc*) ; 
 int /*<<< orphan*/  rk_spi_fill_txfifo (struct rk_spi_softc*) ; 

__attribute__((used)) static int
rk_spi_xfer_buf(struct rk_spi_softc *sc, void *rxbuf, void *txbuf, uint32_t len)
{
	int err;

	if (len == 0)
		return (0);

	sc->rxbuf = rxbuf;
	sc->rxlen = len;
	sc->rxidx = 0;
	sc->txbuf = txbuf;
	sc->txlen = len;
	sc->txidx = 0;
	sc->intreg = 0;
	rk_spi_fill_txfifo(sc);

	RK_SPI_WRITE_4(sc, RK_SPI_IMR, sc->intreg);

	err = 0;
	while (err == 0 && sc->intreg != 0)
		err = msleep(sc, &sc->mtx, 0, "rk_spi", 10 * hz);

	while (err == 0 && sc->rxidx != sc->txidx) {
		/* read residual data from RX fifo */
		rk_spi_empty_rxfifo(sc);
	}

	if (sc->rxidx != sc->rxlen || sc->txidx != sc->txlen)
		err = EIO;

	return (err);
}