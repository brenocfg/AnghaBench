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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct ns8250_softc {int /*<<< orphan*/  ier; scalar_t__ busy_detect; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_REG_USR ; 
 int IIR_BUSY ; 
 int IIR_NOPEND ; 
 int IIR_RXRDY ; 
 int IIR_TXRDY ; 
 int LSR_BI ; 
 int LSR_OE ; 
 int LSR_RXRDY ; 
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  REG_IIR ; 
 int /*<<< orphan*/  REG_LSR ; 
 int SER_INT_BREAK ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_SIGCHG ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  ns8250_clrint (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

int
ns8250_bus_ipend(struct uart_softc *sc)
{
	struct uart_bas *bas;
	struct ns8250_softc *ns8250;
	int ipend;
	uint8_t iir, lsr;

	ns8250 = (struct ns8250_softc *)sc;
	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	iir = uart_getreg(bas, REG_IIR);

	if (ns8250->busy_detect && (iir & IIR_BUSY) == IIR_BUSY) {
		(void)uart_getreg(bas, DW_REG_USR);
		uart_unlock(sc->sc_hwmtx);
		return (0);
	}
	if (iir & IIR_NOPEND) {
		uart_unlock(sc->sc_hwmtx);
		return (0);
	}
	ipend = 0;
	if (iir & IIR_RXRDY) {
		lsr = uart_getreg(bas, REG_LSR);
		if (lsr & LSR_OE)
			ipend |= SER_INT_OVERRUN;
		if (lsr & LSR_BI)
			ipend |= SER_INT_BREAK;
		if (lsr & LSR_RXRDY)
			ipend |= SER_INT_RXREADY;
	} else {
		if (iir & IIR_TXRDY) {
			ipend |= SER_INT_TXIDLE;
			uart_setreg(bas, REG_IER, ns8250->ier);
			uart_barrier(bas);
		} else
			ipend |= SER_INT_SIGCHG;
	}
	if (ipend == 0)
		ns8250_clrint(bas);
	uart_unlock(sc->sc_hwmtx);
	return (ipend);
}