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
typedef  int u_char ;
struct uart_bas {int dummy; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct ns8250_softc {int ier_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

void
ns8250_bus_grab(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	struct ns8250_softc *ns8250 = (struct ns8250_softc*)sc;
	u_char ier;

	/*
	 * turn off all interrupts to enter polling mode. Leave the
	 * saved mask alone. We'll restore whatever it was in ungrab.
	 * All pending interrupt signals are reset when IER is set to 0.
	 */
	uart_lock(sc->sc_hwmtx);
	ier = uart_getreg(bas, REG_IER);
	uart_setreg(bas, REG_IER, ier & ns8250->ier_mask);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
}