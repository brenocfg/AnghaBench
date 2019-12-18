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
struct z8530_softc {int txidle; } ;
struct uart_bas {int dummy; } ;
struct uart_softc {int sc_txbusy; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/ * sc_txbuf; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int BES_TXE ; 
 int /*<<< orphan*/  REG_DATA ; 
 int /*<<< orphan*/  RR_BES ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getmreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
z8530_bus_transmit(struct uart_softc *sc)
{
	struct z8530_softc *z8530 = (struct z8530_softc*)sc;
	struct uart_bas *bas;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	while (!(uart_getmreg(bas, RR_BES) & BES_TXE))
		;
	uart_setreg(bas, REG_DATA, sc->sc_txbuf[0]);
	uart_barrier(bas);
	sc->sc_txbusy = 1;
	z8530->txidle = 1;	/* Report SER_INT_TXIDLE again. */
	uart_unlock(sc->sc_hwmtx);
	return (0);
}