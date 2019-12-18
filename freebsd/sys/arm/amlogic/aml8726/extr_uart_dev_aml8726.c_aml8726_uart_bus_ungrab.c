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
 int /*<<< orphan*/  AML_UART_MISC_RECV_IRQ_CNT_MASK ; 
 int /*<<< orphan*/  AML_UART_MISC_REG ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aml8726_uart_bus_ungrab(struct uart_softc *sc)
{
	struct uart_bas *bas;
	uint32_t cr;
	uint32_t mr;

	/*
	 * The RX FIFO level being set indicates that the device
	 * is currently attached meaning the receive interrupt
	 * should be enabled.
	 */

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	mr = uart_getreg(bas, AML_UART_MISC_REG);
	mr &= AML_UART_MISC_RECV_IRQ_CNT_MASK;

	if (mr != 0) {
		cr = uart_getreg(bas, AML_UART_CONTROL_REG);
		cr |= AML_UART_CONTROL_RX_INT_EN;
		uart_setreg(bas, AML_UART_CONTROL_REG, cr);
		uart_barrier(bas);
	}

	uart_unlock(sc->sc_hwmtx);
}