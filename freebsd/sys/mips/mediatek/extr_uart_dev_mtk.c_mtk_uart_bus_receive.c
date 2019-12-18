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
typedef  int uint8_t ;
struct uart_bas {int dummy; } ;
struct uart_softc {int* sc_rxbuf; size_t sc_rxput; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int /*<<< orphan*/  UART_LSR_REG ; 
 int /*<<< orphan*/  UART_RX_REG ; 
 int UART_STAT_FRAMERR ; 
 int UART_STAT_OVERRUN ; 
 int UART_STAT_PARERR ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_uart_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int xc;
	uint8_t lsr;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	lsr = uart_getreg(bas, UART_LSR_REG);
	while ((lsr & UART_LSR_DR)) {
		if (uart_rx_full(sc)) {
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}
		xc = 0;
		xc = uart_getreg(bas, UART_RX_REG);
		if (lsr & UART_LSR_FE)
			xc |= UART_STAT_FRAMERR;
		if (lsr & UART_LSR_PE)
			xc |= UART_STAT_PARERR;
		if (lsr & UART_LSR_OE)
			xc |= UART_STAT_OVERRUN;
		uart_barrier(bas);
		uart_rx_put(sc, xc);
		lsr = uart_getreg(bas, UART_LSR_REG);
	}

	uart_unlock(sc->sc_hwmtx);
	return (0);
}