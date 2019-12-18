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
struct mv_spi_softc {int sc_flags; scalar_t__ sc_written; scalar_t__ sc_len; scalar_t__ sc_read; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int MV_SPI_BUSY ; 
 int /*<<< orphan*/  MV_SPI_LOCK (struct mv_spi_softc*) ; 
 int /*<<< orphan*/  MV_SPI_UNLOCK (struct mv_spi_softc*) ; 
 int /*<<< orphan*/  mv_spi_rx_byte (struct mv_spi_softc*) ; 
 int /*<<< orphan*/  mv_spi_tx_byte (struct mv_spi_softc*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mv_spi_intr(void *arg)
{
	struct mv_spi_softc *sc;

	sc = (struct mv_spi_softc *)arg;
	MV_SPI_LOCK(sc);

	/* Filter stray interrupts. */
	if ((sc->sc_flags & MV_SPI_BUSY) == 0) {
		MV_SPI_UNLOCK(sc);
		return;
	}

	/* RX */
	mv_spi_rx_byte(sc);

	/* TX */
	mv_spi_tx_byte(sc);

	/* Check for end of transfer. */
	if (sc->sc_written == sc->sc_len && sc->sc_read == sc->sc_len)
		wakeup(sc->sc_dev);

	MV_SPI_UNLOCK(sc);
}