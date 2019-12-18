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
typedef  int uint32_t ;
struct uart_bas {int dummy; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct uart_mvebu_softc {int intrm; } ;

/* Variables and functions */
 int CTRL_INTR_MASK ; 
 int /*<<< orphan*/  UART_CTRL ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uart_mvebu_bus_ungrab(struct uart_softc *sc)
{
	struct uart_mvebu_softc *msc = (struct uart_mvebu_softc *)sc;
	struct uart_bas *bas = &sc->sc_bas;
	uint32_t ctrl;

	/* Restore interrupts */
	uart_lock(sc->sc_hwmtx);
	ctrl = uart_getreg(bas, UART_CTRL) & ~CTRL_INTR_MASK;
	uart_setreg(bas, UART_CTRL, ctrl | msc->intrm);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
}