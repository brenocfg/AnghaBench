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
struct uart_softc {size_t sc_rxput; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/ * sc_rxbuf; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int RBR_BRK_DET ; 
 int RBR_FRM_ERR_DET ; 
 int RBR_OVR_ERR_DET ; 
 int RBR_PAR_ERR_DET ; 
 int STAT_RX_FIFO_EMPT ; 
 int /*<<< orphan*/  UART_FLUSH_RECEIVER ; 
 int /*<<< orphan*/  UART_RBR ; 
 int /*<<< orphan*/  UART_STAT ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_mvebu_bus_flush (struct uart_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

int
uart_mvebu_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	uint32_t xc;
	int rx, er;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	while (!(uart_getreg(bas, UART_STAT) & STAT_RX_FIFO_EMPT)) {
		if (uart_rx_full(sc)) {
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}

		xc = uart_getreg(bas, UART_RBR);
		rx = xc & 0xff;
		er = xc & 0xf000;
		/*
		 * Formula which translates marvell error bits
		 * Only valid when CTRL_ST_MIRR_EN is set
		 */
		er = (er & RBR_BRK_DET) >> 7 |
		    (er & RBR_FRM_ERR_DET) >> 5 |
		    (er & RBR_PAR_ERR_DET) >> 2 |
		    (er & RBR_OVR_ERR_DET) >> 2;

		uart_rx_put(sc, rx | er);
		uart_barrier(bas);
	}
	/*
	 * uart_if.m says that receive interrupt
	 * should be cleared, so we need to reset
	 * RX FIFO
	 */

	if (!(uart_getreg(bas, UART_STAT) & STAT_RX_FIFO_EMPT)) {
		uart_mvebu_bus_flush(sc, UART_FLUSH_RECEIVER);
	}

	uart_unlock(sc->sc_hwmtx);
	return (0);
}