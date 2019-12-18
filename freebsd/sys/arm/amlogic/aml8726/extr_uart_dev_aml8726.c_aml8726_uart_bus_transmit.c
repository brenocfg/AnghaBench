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
struct uart_softc {int sc_txdatasz; int* sc_txbuf; int sc_txbusy; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_UART_CONTROL_REG ; 
 int AML_UART_CONTROL_TX_INT_EN ; 
 int /*<<< orphan*/  AML_UART_STATUS_REG ; 
 int AML_UART_STATUS_TX_FIFO_EMPTY ; 
 int /*<<< orphan*/  AML_UART_WFIFO_REG ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_uart_bus_transmit(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int i;
	uint32_t cr;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	/*
	 * Wait for sufficient space since aml8726_uart_putc
	 * may have been called after SER_INT_TXIDLE occurred.
	 */
	while ((uart_getreg(bas, AML_UART_STATUS_REG) &
	    AML_UART_STATUS_TX_FIFO_EMPTY) == 0)
		cpu_spinwait();

	for (i = 0; i < sc->sc_txdatasz; i++) {
		uart_setreg(bas, AML_UART_WFIFO_REG, sc->sc_txbuf[i]);
		uart_barrier(bas);
	}

	sc->sc_txbusy = 1;

	cr = uart_getreg(bas, AML_UART_CONTROL_REG);
	cr |= AML_UART_CONTROL_TX_INT_EN;
	uart_setreg(bas, AML_UART_CONTROL_REG, cr);
	uart_barrier(bas);

	uart_unlock(sc->sc_hwmtx);

	return (0);
}