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
struct uart_softc {struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_UART_CONTROL_REG ; 
 int AML_UART_CONTROL_RX_INT_EN ; 
 int AML_UART_CONTROL_TX_INT_EN ; 
 int AML_UART_MISC_RECV_IRQ_CNT_MASK ; 
 int /*<<< orphan*/  AML_UART_MISC_REG ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
aml8726_uart_bus_detach(struct uart_softc *sc)
{
	struct uart_bas *bas;
	uint32_t cr;
	uint32_t mr;

	bas = &sc->sc_bas;

	/* Disable all interrupt sources. */
	cr = uart_getreg(bas, AML_UART_CONTROL_REG);
	cr &= ~(AML_UART_CONTROL_TX_INT_EN | AML_UART_CONTROL_RX_INT_EN);
	uart_setreg(bas, AML_UART_CONTROL_REG, cr);
	uart_barrier(bas);

	/* Clear RX FIFO level for generating interrupts. */
	mr = uart_getreg(bas, AML_UART_MISC_REG);
	mr &= ~AML_UART_MISC_RECV_IRQ_CNT_MASK;
	uart_setreg(bas, AML_UART_MISC_REG, mr);
	uart_barrier(bas);

	return (0);
}