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
struct uart_softc {int* sc_rxbuf; size_t sc_rxput; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATEN ; 
 int /*<<< orphan*/  BRK ; 
 int /*<<< orphan*/  ENA (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FLD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRMERR ; 
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVRRUN ; 
 int /*<<< orphan*/  PRERR ; 
 int /*<<< orphan*/  RDR ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RRDYEN ; 
 int UART_STAT_BREAK ; 
 int UART_STAT_FRAMERR ; 
 int UART_STAT_OVERRUN ; 
 int UART_STAT_PARERR ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UCR2 ; 
 int /*<<< orphan*/  URXD ; 
 int /*<<< orphan*/  USR2 ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_uart_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int xc, out;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	/*
	 * Empty the rx fifo.  We get the RRDY interrupt when IMX_RXFIFO_LEVEL
	 * (the rx high-water level) is reached, but we set sc_rxfifosz to the
	 * full hardware fifo size, so we can safely process however much is
	 * there, not just the highwater size.
	 */
	while (IS(bas, USR2, RDR)) {
		if (uart_rx_full(sc)) {
			/* No space left in input buffer */
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}
		xc = GETREG(bas, REG(URXD));
		out = xc & 0x000000ff;
		if (xc & FLD(URXD, FRMERR))
			out |= UART_STAT_FRAMERR;
		if (xc & FLD(URXD, PRERR))
			out |= UART_STAT_PARERR;
		if (xc & FLD(URXD, OVRRUN))
			out |= UART_STAT_OVERRUN;
		if (xc & FLD(URXD, BRK))
			out |= UART_STAT_BREAK;

		uart_rx_put(sc, out);
	}
	ENA(bas, UCR1, RRDYEN);
	ENA(bas, UCR2, ATEN);

	uart_unlock(sc->sc_hwmtx);
	return (0);
}