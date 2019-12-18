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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; scalar_t__ sc_txbusy; struct uart_bas sc_bas; } ;
struct uart_pl011_softc {int imsc; } ;

/* Variables and functions */
 int RIS_BE ; 
 int RIS_OE ; 
 int RIS_RTIM ; 
 int SER_INT_BREAK ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  UART_IMSC ; 
 int /*<<< orphan*/  UART_MIS ; 
 int UART_RXREADY ; 
 int UART_TXEMPTY ; 
 int __uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_pl011_bus_ipend(struct uart_softc *sc)
{
	struct uart_pl011_softc *psc;
	struct uart_bas *bas;
	uint32_t ints;
	int ipend;

	psc = (struct uart_pl011_softc *)sc;
	bas = &sc->sc_bas;

	uart_lock(sc->sc_hwmtx);
	ints = __uart_getreg(bas, UART_MIS);
	ipend = 0;

	if (ints & (UART_RXREADY | RIS_RTIM))
		ipend |= SER_INT_RXREADY;
	if (ints & RIS_BE)
		ipend |= SER_INT_BREAK;
	if (ints & RIS_OE)
		ipend |= SER_INT_OVERRUN;
	if (ints & UART_TXEMPTY) {
		if (sc->sc_txbusy)
			ipend |= SER_INT_TXIDLE;

		/* Disable TX interrupt */
		__uart_setreg(bas, UART_IMSC, psc->imsc & ~UART_TXEMPTY);
	}

	uart_unlock(sc->sc_hwmtx);

	return (ipend);
}