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
 int DR_RX_FIFO_EMPTY ; 
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_STATUS_ACK ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DR ; 
 int /*<<< orphan*/  UART_INT_STATUS ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lowrisc_uart_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	uint32_t reg;

	bas = &sc->sc_bas;

	uart_lock(sc->sc_hwmtx);

	do {
		if (uart_rx_full(sc)) {
			/* No space left in the input buffer */
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}
		reg = GETREG(bas, UART_DR);
		SETREG(bas, UART_INT_STATUS, INT_STATUS_ACK);
		uart_rx_put(sc, reg & 0xff);
	} while ((reg & DR_RX_FIFO_EMPTY) == 0);

	uart_unlock(sc->sc_hwmtx);

	return (0);
}