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
struct uart_mtk_softc {int ier; int ier_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER_REG ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

void
mtk_uart_bus_grab(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	struct uart_mtk_softc *usc = (struct uart_mtk_softc *)sc;

	uart_lock(sc->sc_hwmtx);
	usc->ier = uart_getreg(bas, UART_IER_REG);
	uart_setreg(bas, UART_IER_REG, usc->ier & usc->ier_mask);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
}