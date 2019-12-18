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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int DR_RX_FIFO_EMPTY ; 
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_STATUS_ACK ; 
 int SER_INT_RXREADY ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DR ; 
 int /*<<< orphan*/  UART_INT_STATUS ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lowrisc_uart_bus_ipend(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int ipend;

	bas = &sc->sc_bas;

	ipend = 0;

	uart_lock(sc->sc_hwmtx);
	if ((GETREG(bas, UART_DR) & DR_RX_FIFO_EMPTY) == 0)
		ipend |= SER_INT_RXREADY;
	SETREG(bas, UART_INT_STATUS, INT_STATUS_ACK);
	uart_unlock(sc->sc_hwmtx);

	return (ipend);
}