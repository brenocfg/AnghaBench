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
struct oct16550_softc {int ier; } ;

/* Variables and functions */
 int IER_ETXRDY ; 
 int /*<<< orphan*/  REG_DATA ; 
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  oct16550_delay (struct uart_bas*) ; 
 int /*<<< orphan*/  oct16550_putc (struct uart_bas*,int) ; 
 int /*<<< orphan*/  oct16550_wait_txhr_empty (struct uart_bas*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
oct16550_bus_transmit (struct uart_softc *sc)
{
	struct oct16550_softc *oct16550 = (struct oct16550_softc*)sc;
	struct uart_bas *bas;
	int i;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
#ifdef NO_UART_INTERRUPTS
        for (i = 0; i < sc->sc_txdatasz; i++) {
            oct16550_putc(bas, sc->sc_txbuf[i]);
        }
#else

        oct16550_wait_txhr_empty(bas, 100, oct16550_delay(bas));
	uart_setreg(bas, REG_IER, oct16550->ier | IER_ETXRDY);
	uart_barrier(bas);

	for (i = 0; i < sc->sc_txdatasz; i++) {
		uart_setreg(bas, REG_DATA, sc->sc_txbuf[i]);
		uart_barrier(bas);
	}
	sc->sc_txbusy = 1;
#endif
	uart_unlock(sc->sc_hwmtx);
	return (0);
}