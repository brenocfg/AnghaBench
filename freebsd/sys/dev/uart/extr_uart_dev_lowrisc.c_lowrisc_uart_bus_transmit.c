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
struct uart_softc {int sc_txdatasz; int* sc_txbuf; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int DR_TX_FIFO_FULL ; 
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UART_DR ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lowrisc_uart_bus_transmit(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int i;

	bas = &sc->sc_bas;

	uart_lock(sc->sc_hwmtx);
	for (i = 0; i < sc->sc_txdatasz; i++) {
		while (GETREG(bas, UART_DR) & DR_TX_FIFO_FULL)
			;
		SETREG(bas, UART_DR, sc->sc_txbuf[i] & 0xff);
	}
	uart_unlock(sc->sc_hwmtx);

	return (0);
}