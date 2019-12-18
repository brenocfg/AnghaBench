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
struct uart_softc {size_t sc_rxput; int /*<<< orphan*/ * sc_rxbuf; scalar_t__ sc_opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  SER_INT_RXREADY ; 
 int /*<<< orphan*/  UART_FLUSH (struct uart_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_FLUSH_RECEIVER ; 
 int /*<<< orphan*/  UART_RECEIVE (struct uart_softc*) ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 scalar_t__ uart_rx_put (struct uart_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_sched_softih (struct uart_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
uart_intr_overrun(void *arg)
{
	struct uart_softc *sc = arg;

	if (sc->sc_opened) {
		UART_RECEIVE(sc);
		if (uart_rx_put(sc, UART_STAT_OVERRUN))
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
		uart_sched_softih(sc, SER_INT_RXREADY);
	}
	UART_FLUSH(sc, UART_FLUSH_RECEIVER);
	return (0);
}