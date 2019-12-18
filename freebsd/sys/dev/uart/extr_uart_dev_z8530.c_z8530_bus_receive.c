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
 int BES_RXA ; 
 int /*<<< orphan*/  CR_RSTERR ; 
 int /*<<< orphan*/  REG_CTRL ; 
 int /*<<< orphan*/  REG_DATA ; 
 int /*<<< orphan*/  RR_BES ; 
 int /*<<< orphan*/  RR_SRC ; 
 int SRC_FE ; 
 int SRC_OVR ; 
 int SRC_PE ; 
 int UART_STAT_FRAMERR ; 
 int UART_STAT_OVERRUN ; 
 int UART_STAT_PARERR ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getmreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
z8530_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int xc;
	uint8_t bes, src;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	bes = uart_getmreg(bas, RR_BES);
	while (bes & BES_RXA) {
		if (uart_rx_full(sc)) {
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}
		xc = uart_getreg(bas, REG_DATA);
		uart_barrier(bas);
		src = uart_getmreg(bas, RR_SRC);
		if (src & SRC_FE)
			xc |= UART_STAT_FRAMERR;
		if (src & SRC_PE)
			xc |= UART_STAT_PARERR;
		if (src & SRC_OVR)
			xc |= UART_STAT_OVERRUN;
		uart_rx_put(sc, xc);
		if (src & (SRC_FE | SRC_PE | SRC_OVR)) {
			uart_setreg(bas, REG_CTRL, CR_RSTERR);
			uart_barrier(bas);
		}
		bes = uart_getmreg(bas, RR_BES);
	}
	/* Discard everything left in the Rx FIFO. */
	while (bes & BES_RXA) {
		(void)uart_getreg(bas, REG_DATA);
		uart_barrier(bas);
		src = uart_getmreg(bas, RR_SRC);
		if (src & (SRC_FE | SRC_PE | SRC_OVR)) {
			uart_setreg(bas, REG_CTRL, CR_RSTERR);
			uart_barrier(bas);
		}
		bes = uart_getmreg(bas, RR_BES);
	}
	uart_unlock(sc->sc_hwmtx);
	return (0);
}