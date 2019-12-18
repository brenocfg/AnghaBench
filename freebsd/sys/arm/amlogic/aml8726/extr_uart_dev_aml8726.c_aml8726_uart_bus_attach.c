#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct uart_bas {scalar_t__ rclk; } ;
struct uart_softc {TYPE_1__* sc_sysdev; int /*<<< orphan*/  sc_dev; struct uart_bas sc_bas; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int AML_UART_CONTROL_CLR_ERR ; 
 int /*<<< orphan*/  AML_UART_CONTROL_REG ; 
 int AML_UART_CONTROL_RX_EN ; 
 int AML_UART_CONTROL_RX_INT_EN ; 
 int AML_UART_CONTROL_RX_RST ; 
 int AML_UART_CONTROL_TWO_WIRE_EN ; 
 int AML_UART_CONTROL_TX_EN ; 
 int AML_UART_CONTROL_TX_INT_EN ; 
 int AML_UART_CONTROL_TX_RST ; 
 int AML_UART_MISC_RECV_IRQ_CNT_MASK ; 
 int AML_UART_MISC_RECV_IRQ_CNT_SHIFT ; 
 int /*<<< orphan*/  AML_UART_MISC_REG ; 
 int AML_UART_MISC_XMIT_IRQ_CNT_MASK ; 
 int AML_UART_MISC_XMIT_IRQ_CNT_SHIFT ; 
 int ENXIO ; 
 scalar_t__ UART_DEV_CONSOLE ; 
 scalar_t__ aml8726_uart_bus_clk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_uart_bus_getsig (struct uart_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
aml8726_uart_bus_attach(struct uart_softc *sc)
{
	struct uart_bas *bas;
	uint32_t cr;
	uint32_t mr;

	bas = &sc->sc_bas;

	bas->rclk = aml8726_uart_bus_clk(ofw_bus_get_node(sc->sc_dev));

	if (bas->rclk == 0) {
		device_printf(sc->sc_dev, "missing clocks attribute in FDT\n");
		return (ENXIO);
	}

	cr = uart_getreg(bas, AML_UART_CONTROL_REG);
	/* Disable all interrupt sources. */
	cr &= ~(AML_UART_CONTROL_TX_INT_EN | AML_UART_CONTROL_RX_INT_EN);
	/* Ensure the reset bits are clear. */
	cr &= ~(AML_UART_CONTROL_TX_RST | AML_UART_CONTROL_RX_RST);

	/*
	 * Reset the transmitter and receiver only if not acting as a
	 * console, otherwise it means that:
	 *
	 * 1) aml8726_uart_init was already called which did the reset
	 *
	 * 2) there may be console bytes sitting in the transmit fifo
	 */
	if (sc->sc_sysdev != NULL && sc->sc_sysdev->type == UART_DEV_CONSOLE)
		;
	else
		cr |= (AML_UART_CONTROL_TX_RST | AML_UART_CONTROL_RX_RST);

	/* Default to two wire mode. */
	cr |= AML_UART_CONTROL_TWO_WIRE_EN;
	/* Enable the transmitter and receiver. */
	cr |= (AML_UART_CONTROL_TX_EN | AML_UART_CONTROL_RX_EN);
	/* Reset error bits. */
	cr |= AML_UART_CONTROL_CLR_ERR;
	uart_setreg(bas, AML_UART_CONTROL_REG, cr);
	uart_barrier(bas);

	/* Set FIFO levels for generating interrupts. */
	mr = uart_getreg(bas, AML_UART_MISC_REG);
	mr &= ~AML_UART_MISC_XMIT_IRQ_CNT_MASK;
	mr |= (0 << AML_UART_MISC_XMIT_IRQ_CNT_SHIFT);
	mr &= ~AML_UART_MISC_RECV_IRQ_CNT_MASK;
	mr |= (1 << AML_UART_MISC_RECV_IRQ_CNT_SHIFT);
	uart_setreg(bas, AML_UART_MISC_REG, mr);
	uart_barrier(bas);

	aml8726_uart_bus_getsig(sc);

	/* Ensure the reset bits are clear. */
	cr &= ~(AML_UART_CONTROL_TX_RST | AML_UART_CONTROL_RX_RST);
	cr &= ~AML_UART_CONTROL_CLR_ERR;
	/* Enable the receive interrupt. */
	cr |= AML_UART_CONTROL_RX_INT_EN;
	uart_setreg(bas, AML_UART_CONTROL_REG, cr);
	uart_barrier(bas);

	return (0);
}