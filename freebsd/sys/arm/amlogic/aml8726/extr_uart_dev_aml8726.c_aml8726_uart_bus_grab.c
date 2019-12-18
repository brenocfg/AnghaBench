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
typedef  int /*<<< orphan*/  uint32_t ;
struct uart_bas {int dummy; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_UART_CONTROL_REG ; 
 int /*<<< orphan*/  AML_UART_CONTROL_RX_INT_EN ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aml8726_uart_bus_grab(struct uart_softc *sc)
{
	struct uart_bas *bas;
	uint32_t cr;

	/*
	 * Disable the receive interrupt to avoid a race between
	 * aml8726_uart_getc and aml8726_uart_bus_receive which
	 * can trigger:
	 *
	 *   panic: bad stray interrupt
	 *
	 * due to the RX FIFO receiving a character causing an
	 * interrupt which gets serviced after aml8726_uart_getc
	 * has been called (meaning the RX FIFO is now empty).
	 */

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	cr = uart_getreg(bas, AML_UART_CONTROL_REG);
	cr &= ~AML_UART_CONTROL_RX_INT_EN;
	uart_setreg(bas, AML_UART_CONTROL_REG, cr);
	uart_barrier(bas);

	uart_unlock(sc->sc_hwmtx);
}