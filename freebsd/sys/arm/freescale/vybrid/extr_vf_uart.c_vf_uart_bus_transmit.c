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
 int /*<<< orphan*/  UART_C2 ; 
 int UART_C2_TIE ; 
 int /*<<< orphan*/  UART_D ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vf_uart_bus_transmit(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	int i;
	int reg;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	/* Fill TX FIFO */
	for (i = 0; i < sc->sc_txdatasz; i++) {
		uart_setreg(bas, UART_D, sc->sc_txbuf[i] & 0xff);
		uart_barrier(&sc->sc_bas);
	}

	sc->sc_txbusy = 1;

	/* Call me when ready */
	reg = uart_getreg(bas, UART_C2);
	reg |= (UART_C2_TIE);
	uart_setreg(bas, UART_C2, reg);

	uart_unlock(sc->sc_hwmtx);

	return (0);
}