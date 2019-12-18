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

/* Variables and functions */
 int /*<<< orphan*/  ENA (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRDYEN ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UTXD ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_uart_bus_transmit(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	int i;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	/*
	 * Fill the tx fifo.  The uart core puts at most IMX_TXFIFO_LEVEL bytes
	 * into the txbuf (because that's what sc_txfifosz is set to), and
	 * because we got the TRDY (low-water reached) interrupt we know at
	 * least that much space is available in the fifo.
	 */
	for (i = 0; i < sc->sc_txdatasz; i++) {
		SETREG(bas, REG(UTXD), sc->sc_txbuf[i] & 0xff);
	}
	sc->sc_txbusy = 1;
	ENA(bas, UCR1, TRDYEN);

	uart_unlock(sc->sc_hwmtx);

	return (0);
}