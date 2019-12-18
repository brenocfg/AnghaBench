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
 int CTRL_INTR_MASK ; 
 int CTRL_IPEND_MASK ; 
 int /*<<< orphan*/  UART_CTRL ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_mvebu_bus_attach(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int ctrl;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	ctrl = uart_getreg(bas, UART_CTRL);

	/* Enable interrupts */
	ctrl &=~ CTRL_INTR_MASK;
	ctrl |= CTRL_IPEND_MASK;

	/* Set interrupts */
	uart_setreg(bas, UART_CTRL, ctrl);
	uart_barrier(bas);

	uart_unlock(sc->sc_hwmtx);

	return (0);
}