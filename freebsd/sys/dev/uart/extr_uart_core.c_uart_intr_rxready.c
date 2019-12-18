#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_softc {int sc_rxput; int sc_rxbufsz; int sc_rxget; scalar_t__ sc_opened; int /*<<< orphan*/  sc_altbrk; int /*<<< orphan*/ * sc_rxbuf; TYPE_1__* sc_sysdev; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SER_INT_RXREADY ; 
 scalar_t__ UART_DEV_CONSOLE ; 
 int /*<<< orphan*/  UART_RECEIVE (struct uart_softc*) ; 
 int /*<<< orphan*/  kdb_alt_break (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_sched_softih (struct uart_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
uart_intr_rxready(void *arg)
{
	struct uart_softc *sc = arg;
	int rxp;

	rxp = sc->sc_rxput;
	UART_RECEIVE(sc);
#if defined(KDB)
	if (sc->sc_sysdev != NULL && sc->sc_sysdev->type == UART_DEV_CONSOLE) {
		while (rxp != sc->sc_rxput) {
			kdb_alt_break(sc->sc_rxbuf[rxp++], &sc->sc_altbrk);
			if (rxp == sc->sc_rxbufsz)
				rxp = 0;
		}
	}
#endif
	if (sc->sc_opened)
		uart_sched_softih(sc, SER_INT_RXREADY);
	else
		sc->sc_rxput = sc->sc_rxget;	/* Ignore received data. */
	return (1);
}