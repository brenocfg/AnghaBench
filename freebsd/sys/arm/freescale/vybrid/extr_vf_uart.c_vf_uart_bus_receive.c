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
 int /*<<< orphan*/  UART_C2 ; 
 int UART_C2_RIE ; 
 int /*<<< orphan*/  UART_D ; 
 int /*<<< orphan*/  UART_S1 ; 
 int UART_S1_RDRF ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vf_uart_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int reg;
	int c;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	/* Read FIFO */
	while (uart_getreg(bas, UART_S1) & UART_S1_RDRF) {
		if (uart_rx_full(sc)) {
		/* No space left in input buffer */
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}

		c = uart_getreg(bas, UART_D);
		uart_rx_put(sc, c);
	}

	/* Reenable Data Ready interrupt */
	reg = uart_getreg(bas, UART_C2);
	reg |= (UART_C2_RIE);
	uart_setreg(bas, UART_C2, reg);

	uart_unlock(sc->sc_hwmtx);
	return (0);
}