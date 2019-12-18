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
struct msm_uart_softc {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DM_IMR ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
msm_bus_ungrab(struct uart_softc *sc)
{
	struct msm_uart_softc *u = (struct msm_uart_softc *)sc;
	struct uart_bas *bas = &sc->sc_bas;

	/*
	 * Restore previous interrupt mask
	 */
	uart_lock(sc->sc_hwmtx);
	SETREG(bas, UART_DM_IMR, u->ier);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
}