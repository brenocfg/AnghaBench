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
struct uart_softc {scalar_t__ sc_txbusy; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct msm_uart_softc {int ier; } ;

/* Variables and functions */
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int UART_DM_CLEAR_TX_READY ; 
 int /*<<< orphan*/  UART_DM_CR ; 
 int /*<<< orphan*/  UART_DM_IMR ; 
 int /*<<< orphan*/  UART_DM_MISR ; 
 int UART_DM_RESET_STALE_INT ; 
 int UART_DM_RXLEV ; 
 int UART_DM_RXSTALE ; 
 int UART_DM_STALE_EVENT_DISABLE ; 
 int UART_DM_TXLEV ; 
 int UART_DM_TX_READY ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msm_bus_ipend(struct uart_softc *sc)
{
	struct msm_uart_softc *u = (struct msm_uart_softc *)sc;
	struct uart_bas *bas = &sc->sc_bas;
	uint32_t isr;
	int ipend;

	uart_lock(sc->sc_hwmtx);

	/* Get ISR status */
	isr = GETREG(bas, UART_DM_MISR);

	ipend = 0;

	/* Uart RX starting, notify upper layer */
	if (isr & UART_DM_RXLEV) {
		u->ier &= ~UART_DM_RXLEV;
		SETREG(bas, UART_DM_IMR, u->ier);
		uart_barrier(bas);
		ipend |= SER_INT_RXREADY;
	}

	/* Stale RX interrupt */
	if (isr & UART_DM_RXSTALE) {
		/* Disable and reset it */
		SETREG(bas, UART_DM_CR, UART_DM_STALE_EVENT_DISABLE);
		SETREG(bas, UART_DM_CR, UART_DM_RESET_STALE_INT);
		uart_barrier(bas);
		ipend |= SER_INT_RXREADY;
	}

	/* TX READY interrupt */
	if (isr & UART_DM_TX_READY) {
		/* Clear  TX Ready */
		SETREG(bas, UART_DM_CR, UART_DM_CLEAR_TX_READY);

		/* Disable TX_READY */
		u->ier &= ~UART_DM_TX_READY;
		SETREG(bas, UART_DM_IMR, u->ier);
		uart_barrier(bas);

		if (sc->sc_txbusy != 0)
			ipend |= SER_INT_TXIDLE;
	}

	if (isr & UART_DM_TXLEV) {
		/* TX FIFO is empty */
		u->ier &= ~UART_DM_TXLEV;
		SETREG(bas, UART_DM_IMR, u->ier);
		uart_barrier(bas);

		if (sc->sc_txbusy != 0)
			ipend |= SER_INT_TXIDLE;
	}

	uart_unlock(sc->sc_hwmtx);
	return (ipend);
}