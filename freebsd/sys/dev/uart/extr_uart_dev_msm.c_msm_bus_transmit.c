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
struct msm_uart_softc {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DM_IMR ; 
 int /*<<< orphan*/  UART_DM_TX_READY ; 
 int /*<<< orphan*/  msm_putc (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msm_bus_transmit(struct uart_softc *sc)
{
	struct msm_uart_softc *u = (struct msm_uart_softc *)sc;
	struct uart_bas *bas = &sc->sc_bas;
	int i;

	uart_lock(sc->sc_hwmtx);

	/* Write some data */
	for (i = 0; i < sc->sc_txdatasz; i++) {
		/* Write TX data */
		msm_putc(bas, sc->sc_txbuf[i]);
		uart_barrier(bas);
	}

	/* TX FIFO is empty now, enable TX_READY interrupt */
	u->ier |= UART_DM_TX_READY;
	SETREG(bas, UART_DM_IMR, u->ier);
	uart_barrier(bas);

	/*
	 * Inform upper layer that it is transmitting data to hardware,
	 * this will be cleared when TXIDLE interrupt occurs.
	 */
	sc->sc_txbusy = 1;
	uart_unlock(sc->sc_hwmtx);

	return (0);
}