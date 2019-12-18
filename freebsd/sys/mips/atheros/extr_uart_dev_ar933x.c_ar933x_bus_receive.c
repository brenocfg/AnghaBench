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
struct uart_softc {size_t sc_rxput; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/ * sc_rxbuf; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_DATA_REG ; 
 int /*<<< orphan*/  AR933X_UART_DATA_RX_CSR ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 int ar933x_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 scalar_t__ ar933x_rxready (struct uart_bas*) ; 
 int /*<<< orphan*/  ar933x_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar933x_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	int xc;

	uart_lock(sc->sc_hwmtx);

	/* Loop over until we are full, or no data is available */
	while (ar933x_rxready(bas)) {
		if (uart_rx_full(sc)) {
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}

		/* Read the top of the RX FIFO */
		xc = ar933x_getreg(bas, AR933X_UART_DATA_REG) & 0xff;

		/* Remove that entry from said RX FIFO */
		ar933x_setreg(bas, AR933X_UART_DATA_REG,
		    AR933X_UART_DATA_RX_CSR);
		uart_barrier(bas);

		/* XXX frame, parity error */
		uart_rx_put(sc, xc);
	}

	/*
	 * XXX TODO: Discard everything left in the Rx FIFO?
	 * XXX only if we've hit an overrun condition?
	 */

	uart_unlock(sc->sc_hwmtx);

	return (0);
}