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
struct spi_command {scalar_t__ tx_cmd_sz; scalar_t__ rx_cmd_sz; scalar_t__ tx_data_sz; scalar_t__ rx_data_sz; } ;
struct intelspi_softc {int sc_flags; scalar_t__ sc_len; int /*<<< orphan*/  sc_dev; scalar_t__ sc_written; scalar_t__ sc_read; struct spi_command* sc_cmd; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_HIGH ; 
 int /*<<< orphan*/  CS_LOW ; 
 int EINTR ; 
 int EIO ; 
 int EWOULDBLOCK ; 
 int INTELSPI_BUSY ; 
 int /*<<< orphan*/  INTELSPI_LOCK (struct intelspi_softc*) ; 
 int INTELSPI_READ (struct intelspi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTELSPI_SSPREG_SSCR1 ; 
 int /*<<< orphan*/  INTELSPI_UNLOCK (struct intelspi_softc*) ; 
 int /*<<< orphan*/  INTELSPI_WRITE (struct intelspi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int SSCR1_RIE ; 
 int SSCR1_TIE ; 
 int SSCR1_TINTE ; 
 struct intelspi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  intelspi_set_cs (struct intelspi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intelspi_transact (struct intelspi_softc*) ; 
 int mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intelspi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct intelspi_softc *sc;
	int err;
	uint32_t sscr1;

	sc = device_get_softc(dev);
	err = 0;

	KASSERT(cmd->tx_cmd_sz == cmd->rx_cmd_sz, 
	    ("TX/RX command sizes should be equal"));
	KASSERT(cmd->tx_data_sz == cmd->rx_data_sz, 
	    ("TX/RX data sizes should be equal"));

	INTELSPI_LOCK(sc);

	/* If the controller is in use wait until it is available. */
	while (sc->sc_flags & INTELSPI_BUSY) {
		err = mtx_sleep(dev, &sc->sc_mtx, 0, "intelspi", 0);
		if (err == EINTR) {
			INTELSPI_UNLOCK(sc);
			return (err);
		}
	}

	/* Now we have control over SPI controller. */
	sc->sc_flags = INTELSPI_BUSY;

	/* Save a pointer to the SPI command. */
	sc->sc_cmd = cmd;
	sc->sc_read = 0;
	sc->sc_written = 0;
	sc->sc_len = cmd->tx_cmd_sz + cmd->tx_data_sz;

	/* Enable CS */
	intelspi_set_cs(sc, CS_LOW);
	/* Transfer as much as possible to FIFOs */
	if (!intelspi_transact(sc)) {
		/* If FIFO is not large enough - enable interrupts */
		sscr1 = INTELSPI_READ(sc, INTELSPI_SSPREG_SSCR1);
		sscr1 |= (SSCR1_TIE | SSCR1_RIE | SSCR1_TINTE);
		INTELSPI_WRITE(sc, INTELSPI_SSPREG_SSCR1, sscr1);

		/* and wait for transaction to complete */
		err = mtx_sleep(dev, &sc->sc_mtx, 0, "intelspi", hz * 2);
	}

	/* de-asser CS */
	intelspi_set_cs(sc, CS_HIGH);

	/* Clear transaction details */
	sc->sc_cmd = NULL;
	sc->sc_read = 0;
	sc->sc_written = 0;
	sc->sc_len = 0;

	/* Make sure the SPI engine and interrupts are disabled. */
	sscr1 = INTELSPI_READ(sc, INTELSPI_SSPREG_SSCR1);
	sscr1 &= ~(SSCR1_TIE | SSCR1_RIE | SSCR1_TINTE);
	INTELSPI_WRITE(sc, INTELSPI_SSPREG_SSCR1, sscr1);

	/* Release the controller and wakeup the next thread waiting for it. */
	sc->sc_flags = 0;
	wakeup_one(dev);
	INTELSPI_UNLOCK(sc);

	/*
	 * Check for transfer timeout.  The SPI controller doesn't
	 * return errors.
	 */
	if (err == EWOULDBLOCK) {
		device_printf(sc->sc_dev, "transfer timeout\n");
		err = EIO;
	}

	return (err);
}