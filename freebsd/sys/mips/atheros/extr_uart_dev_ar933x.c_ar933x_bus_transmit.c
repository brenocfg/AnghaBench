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
struct uart_bas {int dummy; } ;
struct uart_softc {int sc_txdatasz; int* sc_txbuf; int sc_txbusy; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct ar933x_softc {int u_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_CS_REG ; 
 int AR933X_UART_CS_TX_BUSY ; 
 int /*<<< orphan*/  AR933X_UART_DATA_REG ; 
 int AR933X_UART_DATA_TX_CSR ; 
 int /*<<< orphan*/  AR933X_UART_INT_EN_REG ; 
 int AR933X_UART_INT_TX_EMPTY ; 
 int ar933x_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar933x_bus_transmit(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	struct ar933x_softc *u = (struct ar933x_softc *)sc;
	int i;

	uart_lock(sc->sc_hwmtx);

	/* Wait for the FIFO to be clear - see above */
	while (ar933x_getreg(bas, AR933X_UART_CS_REG) &
	    AR933X_UART_CS_TX_BUSY)
		;

	/*
	 * Write some data!
	 */
	for (i = 0; i < sc->sc_txdatasz; i++) {
		/* Write the TX data */
		ar933x_setreg(bas, AR933X_UART_DATA_REG,
		    (sc->sc_txbuf[i] & 0xff) | AR933X_UART_DATA_TX_CSR);
		uart_barrier(bas);
	}

	/*
	 * Now that we're transmitting, get interrupt notification
	 * when the FIFO is (almost) empty - see above.
	 */
	u->u_ier |= AR933X_UART_INT_TX_EMPTY;
	ar933x_setreg(bas, AR933X_UART_INT_EN_REG, u->u_ier);
	uart_barrier(bas);

	/*
	 * Inform the upper layer that we are presently transmitting
	 * data to the hardware; this will be cleared when the
	 * TXIDLE interrupt occurs.
	 */
	sc->sc_txbusy = 1;
	uart_unlock(sc->sc_hwmtx);

	return (0);
}