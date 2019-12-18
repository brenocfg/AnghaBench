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
typedef  int /*<<< orphan*/  timeout_t ;
struct uart_softc {int sc_testintr; int /*<<< orphan*/  sc_timer; scalar_t__ sc_polled; scalar_t__ sc_leaving; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_SCHEDULE_THREAD ; 
 int FILTER_STRAY ; 
 int SER_INT_BREAK ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_SIGCHG ; 
 int SER_INT_TXIDLE ; 
 int UART_IPEND (struct uart_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct uart_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  uart_intr_break (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_intr_overrun (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_intr_rxready (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_intr_sigchg (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_intr_txidle (struct uart_softc*) ; 
 int uart_poll_freq ; 

__attribute__((used)) static int
uart_intr(void *arg)
{
	struct uart_softc *sc = arg;
	int cnt, ipend, testintr;

	if (sc->sc_leaving)
		return (FILTER_STRAY);

	cnt = 0;
	testintr = sc->sc_testintr;
	while ((!testintr || cnt < 20) && (ipend = UART_IPEND(sc)) != 0) {
		cnt++;
		if (ipend & SER_INT_OVERRUN)
			uart_intr_overrun(sc);
		if (ipend & SER_INT_BREAK)
			uart_intr_break(sc);
		if (ipend & SER_INT_RXREADY)
			uart_intr_rxready(sc);
		if (ipend & SER_INT_SIGCHG)
			uart_intr_sigchg(sc);
		if (ipend & SER_INT_TXIDLE)
			uart_intr_txidle(sc);
	}

	if (sc->sc_polled) {
		callout_reset(&sc->sc_timer, hz / uart_poll_freq,
		    (timeout_t *)uart_intr, sc);
	}

	return ((cnt == 0) ? FILTER_STRAY :
	    ((testintr && cnt == 20) ? FILTER_SCHEDULE_THREAD :
	    FILTER_HANDLED));
}