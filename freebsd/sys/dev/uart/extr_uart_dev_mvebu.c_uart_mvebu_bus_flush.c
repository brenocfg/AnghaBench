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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int CTRL_RX_FIFO_RST ; 
 int CTRL_TX_FIFO_RST ; 
 int EINVAL ; 
 int /*<<< orphan*/  UART_CTRL ; 
#define  UART_FLUSH_RECEIVER 129 
#define  UART_FLUSH_TRANSMITTER 128 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_mvebu_bus_flush(struct uart_softc *sc, int what)
{
	struct uart_bas *bas;
	int ctrl, ret = 0;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	ctrl = uart_getreg(bas, UART_CTRL);

	switch (what) {
	case UART_FLUSH_RECEIVER:
		uart_setreg(bas, UART_CTRL, ctrl | CTRL_RX_FIFO_RST);
		uart_barrier(bas);
		break;

	case UART_FLUSH_TRANSMITTER:
		uart_setreg(bas, UART_CTRL, ctrl | CTRL_TX_FIFO_RST);
		uart_barrier(bas);
		break;

	default:
		ret = EINVAL;
		break;
	}

	/* Back to normal operation */
	if (!ret) {
		uart_setreg(bas, UART_CTRL, ctrl);
		uart_barrier(bas);
	}

	uart_unlock(sc->sc_hwmtx);
	return (ret);
}