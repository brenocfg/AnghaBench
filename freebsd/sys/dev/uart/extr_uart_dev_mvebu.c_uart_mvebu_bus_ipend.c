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
 int CTRL_TX_IDLE_INT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ONE_FRAME_TIME ; 
 int SER_INT_TXIDLE ; 
 int STAT_TRANS_MASK ; 
 int STAT_TX_FIFO_EMPT ; 
 int STAT_TX_IDLE ; 
 int /*<<< orphan*/  UART_CTRL ; 
 int /*<<< orphan*/  UART_STAT ; 
 int stat_ipend_trans (int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_mvebu_bus_ipend(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int ipend, ctrl, ret = 0;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	ipend = uart_getreg(bas, UART_STAT);
	ctrl = uart_getreg(bas, UART_CTRL);

	if (((ipend & STAT_TX_IDLE) == STAT_TX_IDLE) &&
	    (ctrl & CTRL_TX_IDLE_INT) == CTRL_TX_IDLE_INT) {
		/* Disable TX IDLE Interrupt generation */
		uart_setreg(bas, UART_CTRL, ctrl & ~CTRL_TX_IDLE_INT);
		uart_barrier(bas);

		/* SER_INT_TXIDLE means empty TX FIFO. Wait until it cleans */
		while(!(uart_getreg(bas, UART_STAT) & STAT_TX_FIFO_EMPT))
			DELAY(ONE_FRAME_TIME/2);

		ret |= SER_INT_TXIDLE;
	}

	ret |= stat_ipend_trans(ipend & STAT_TRANS_MASK);

	uart_unlock(sc->sc_hwmtx);

	return (ret);
}