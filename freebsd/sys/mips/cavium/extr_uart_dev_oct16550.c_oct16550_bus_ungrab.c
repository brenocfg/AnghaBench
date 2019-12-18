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
struct oct16550_softc {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oct16550_bus_ungrab(struct uart_softc *sc)
{
	struct oct16550_softc *oct16550 = (struct oct16550_softc*)sc;
	struct uart_bas *bas = &sc->sc_bas;

	/*
	 * Restore previous interrupt mask
	 */
	uart_lock(sc->sc_hwmtx);
	uart_setreg(bas, REG_IER, oct16550->ier);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
}