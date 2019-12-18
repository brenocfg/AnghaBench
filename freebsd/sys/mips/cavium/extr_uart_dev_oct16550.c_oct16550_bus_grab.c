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
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oct16550_bus_grab(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;

	/*
	 * turn off all interrupts to enter polling mode. Leave the
	 * saved mask alone. We'll restore whatever it was in ungrab.
	 * All pending interupt signals are reset when IER is set to 0.
	 */
	uart_lock(sc->sc_hwmtx);
	uart_setreg(bas, REG_IER, 0);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
}