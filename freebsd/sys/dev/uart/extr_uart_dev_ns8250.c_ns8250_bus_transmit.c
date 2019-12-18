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
struct uart_softc {int sc_txdatasz; int* sc_txbuf; int sc_txbusy; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct ns8250_softc {int ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IER_ETXRDY ; 
 int LSR_THRE ; 
 int /*<<< orphan*/  REG_DATA ; 
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  REG_LSR ; 
 int /*<<< orphan*/  SER_INT_TXIDLE ; 
 int /*<<< orphan*/  UART_DRAIN_TRANSMITTER ; 
 scalar_t__ broken_txfifo ; 
 int /*<<< orphan*/  ns8250_drain (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_sched_softih (struct uart_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

int
ns8250_bus_transmit(struct uart_softc *sc)
{
	struct ns8250_softc *ns8250 = (struct ns8250_softc*)sc;
	struct uart_bas *bas;
	int i;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	while ((uart_getreg(bas, REG_LSR) & LSR_THRE) == 0)
		DELAY(4);
	for (i = 0; i < sc->sc_txdatasz; i++) {
		uart_setreg(bas, REG_DATA, sc->sc_txbuf[i]);
		uart_barrier(bas);
	}
	uart_setreg(bas, REG_IER, ns8250->ier | IER_ETXRDY);
	uart_barrier(bas);
	if (broken_txfifo)
		ns8250_drain(bas, UART_DRAIN_TRANSMITTER);
	else
		sc->sc_txbusy = 1;
	uart_unlock(sc->sc_hwmtx);
	if (broken_txfifo)
		uart_sched_softih(sc, SER_INT_TXIDLE);
	return (0);
}