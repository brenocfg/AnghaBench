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

/* Variables and functions */
 int /*<<< orphan*/  AML_UART_CONTROL_REG ; 
 int AML_UART_CONTROL_RX_RST ; 
 int AML_UART_CONTROL_TX_RST ; 
 int UART_FLUSH_RECEIVER ; 
 int UART_FLUSH_TRANSMITTER ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_uart_bus_flush(struct uart_softc *sc, int what)
{
	struct uart_bas *bas;
	uint32_t cr;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	cr = uart_getreg(bas, AML_UART_CONTROL_REG);
	if (what & UART_FLUSH_TRANSMITTER)
		cr |= AML_UART_CONTROL_TX_RST;
	if (what & UART_FLUSH_RECEIVER)
		cr |= AML_UART_CONTROL_RX_RST;
	uart_setreg(bas, AML_UART_CONTROL_REG, cr);
	uart_barrier(bas);

	/* Ensure the reset bits are clear. */
	cr &= ~(AML_UART_CONTROL_TX_RST | AML_UART_CONTROL_RX_RST);
	uart_setreg(bas, AML_UART_CONTROL_REG, cr);
	uart_barrier(bas);

	uart_unlock(sc->sc_hwmtx);

	return (0);
}