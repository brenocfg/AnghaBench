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
struct uart_softc {int sc_txdatasz; int sc_txbusy; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/ * sc_txbuf; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNC_UART_FIFO ; 
 int /*<<< orphan*/  CDNC_UART_IEN_REG ; 
 int /*<<< orphan*/  CDNC_UART_INT_TXEMPTY ; 
 int /*<<< orphan*/  CDNC_UART_ISTAT_REG ; 
 int /*<<< orphan*/  WR4 (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdnc_uart_bus_transmit(struct uart_softc *sc)
{
	int i;
	struct uart_bas *bas = &sc->sc_bas;

	uart_lock(sc->sc_hwmtx);

	/* Clear sticky TXEMPTY status bit. */
	WR4(bas, CDNC_UART_ISTAT_REG, CDNC_UART_INT_TXEMPTY);

	for (i = 0; i < sc->sc_txdatasz; i++)
		WR4(bas, CDNC_UART_FIFO, sc->sc_txbuf[i]);

	/* Enable TX empty interrupt. */
	WR4(bas, CDNC_UART_IEN_REG, CDNC_UART_INT_TXEMPTY);
	sc->sc_txbusy = 1;

	uart_unlock(sc->sc_hwmtx);

	return (0);
}