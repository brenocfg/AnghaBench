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
struct uart_bas {int dummy; } ;
struct uart_softc {size_t sc_rxput; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/ * sc_rxbuf; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int DR_FE ; 
 int DR_PE ; 
 int FR_RXFE ; 
 int /*<<< orphan*/  UART_DR ; 
 int /*<<< orphan*/  UART_FR ; 
 int UART_STAT_FRAMERR ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 int UART_STAT_PARERR ; 
 int __uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_pl011_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	uint32_t ints, xc;
	int rx;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	for (;;) {
		ints = __uart_getreg(bas, UART_FR);
		if (ints & FR_RXFE)
			break;
		if (uart_rx_full(sc)) {
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}

		xc = __uart_getreg(bas, UART_DR);
		rx = xc & 0xff;

		if (xc & DR_FE)
			rx |= UART_STAT_FRAMERR;
		if (xc & DR_PE)
			rx |= UART_STAT_PARERR;

		uart_rx_put(sc, rx);
	}

	uart_unlock(sc->sc_hwmtx);

	return (0);
}