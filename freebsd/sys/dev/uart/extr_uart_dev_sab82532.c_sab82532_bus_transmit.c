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
 scalar_t__ SAB_CMDR ; 
 int /*<<< orphan*/  SAB_CMDR_XF ; 
 int /*<<< orphan*/  SAB_STAR ; 
 int SAB_STAR_CEC ; 
 int SAB_STAR_XFW ; 
 scalar_t__ SAB_XFIFO ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sab82532_bus_transmit(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int i;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	while (!(uart_getreg(bas, SAB_STAR) & SAB_STAR_XFW))
		;
	for (i = 0; i < sc->sc_txdatasz; i++)
		uart_setreg(bas, SAB_XFIFO + i, sc->sc_txbuf[i]);
	uart_barrier(bas);
	while (uart_getreg(bas, SAB_STAR) & SAB_STAR_CEC)
		;
	uart_setreg(bas, SAB_CMDR, SAB_CMDR_XF);
	sc->sc_txbusy = 1;
	uart_unlock(sc->sc_hwmtx);
	return (0);
}