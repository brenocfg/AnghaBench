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
struct msm_uart_softc {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DM_CR ; 
 int /*<<< orphan*/  UART_DM_IMR ; 
 int /*<<< orphan*/  UART_DM_RESET_STALE_INT ; 
 int /*<<< orphan*/  UART_DM_RF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DM_RXLEV ; 
 int /*<<< orphan*/  UART_DM_SR ; 
 int UART_DM_SR_RXRDY ; 
 int /*<<< orphan*/  UART_DM_STALE_EVENT_ENABLE ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msm_bus_receive(struct uart_softc *sc)
{
	struct msm_uart_softc *u = (struct msm_uart_softc *)sc;
	struct uart_bas *bas;
	int c;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	/* Initialize Receive Path and interrupt */
	SETREG(bas, UART_DM_CR, UART_DM_RESET_STALE_INT);
	SETREG(bas, UART_DM_CR, UART_DM_STALE_EVENT_ENABLE);
	u->ier |= UART_DM_RXLEV;
	SETREG(bas, UART_DM_IMR, u->ier);

	/* Loop over until we are full, or no data is available */
	while (uart_getreg(bas, UART_DM_SR) & UART_DM_SR_RXRDY) {
		if (uart_rx_full(sc)) {
			/* No space left in input buffer */
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}

		/* Read RX FIFO */
		c = uart_getreg(bas, UART_DM_RF(0));
		uart_barrier(bas);

		uart_rx_put(sc, c);
	}

	uart_unlock(sc->sc_hwmtx);

	return (0);
}