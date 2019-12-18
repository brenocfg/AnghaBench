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
 int AML_UART_CONTROL_CLR_ERR ; 
 int /*<<< orphan*/  AML_UART_CONTROL_REG ; 
 int /*<<< orphan*/  AML_UART_RFIFO_REG ; 
 int AML_UART_STATUS_FRAME_ERR ; 
 int AML_UART_STATUS_PARITY_ERR ; 
 int /*<<< orphan*/  AML_UART_STATUS_REG ; 
 int AML_UART_STATUS_RX_FIFO_EMPTY ; 
 int UART_STAT_FRAMERR ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 int UART_STAT_PARERR ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_uart_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int xc;
	uint32_t sr;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	sr = uart_getreg(bas, AML_UART_STATUS_REG);
	while ((sr & AML_UART_STATUS_RX_FIFO_EMPTY) == 0) {
		if (uart_rx_full(sc)) {
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}
		xc = uart_getreg(bas, AML_UART_RFIFO_REG) & 0xff;
		if (sr & AML_UART_STATUS_FRAME_ERR)
			xc |= UART_STAT_FRAMERR;
		if (sr & AML_UART_STATUS_PARITY_ERR)
			xc |= UART_STAT_PARERR;
		uart_rx_put(sc, xc);
		sr = uart_getreg(bas, AML_UART_STATUS_REG);
	}
	/* Discard everything left in the RX FIFO. */
	while ((sr & AML_UART_STATUS_RX_FIFO_EMPTY) == 0) {
		(void)uart_getreg(bas, AML_UART_RFIFO_REG);
		sr = uart_getreg(bas, AML_UART_STATUS_REG);
	}
	/* Reset error bits */
	if ((sr & (AML_UART_STATUS_FRAME_ERR | AML_UART_STATUS_PARITY_ERR)) != 0) {
		uart_setreg(bas, AML_UART_CONTROL_REG,
		    (uart_getreg(bas, AML_UART_CONTROL_REG) |
		    AML_UART_CONTROL_CLR_ERR));
		uart_barrier(bas);
		uart_setreg(bas, AML_UART_CONTROL_REG,
		    (uart_getreg(bas, AML_UART_CONTROL_REG) &
		    ~AML_UART_CONTROL_CLR_ERR));
		uart_barrier(bas);
	}

	uart_unlock(sc->sc_hwmtx);

	return (0);
}