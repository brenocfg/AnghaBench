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
 int AML_UART_CONTROL_TX_INT_EN ; 
 int /*<<< orphan*/  AML_UART_STATUS_REG ; 
 int AML_UART_STATUS_RX_FIFO_EMPTY ; 
 int AML_UART_STATUS_RX_FIFO_OVERFLOW ; 
 int AML_UART_STATUS_TX_FIFO_EMPTY ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_uart_bus_ipend(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int ipend;
	uint32_t sr;
	uint32_t cr;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

	ipend = 0;
	sr = uart_getreg(bas, AML_UART_STATUS_REG);
	cr = uart_getreg(bas, AML_UART_CONTROL_REG);

	if ((sr & AML_UART_STATUS_RX_FIFO_OVERFLOW) != 0)
		ipend |= SER_INT_OVERRUN;

	if ((sr & AML_UART_STATUS_TX_FIFO_EMPTY) != 0 &&
	    (cr & AML_UART_CONTROL_TX_INT_EN) != 0) {
		ipend |= SER_INT_TXIDLE;

		cr &= ~AML_UART_CONTROL_TX_INT_EN;
		uart_setreg(bas, AML_UART_CONTROL_REG, cr);
		uart_barrier(bas);
	}

	if ((sr & AML_UART_STATUS_RX_FIFO_EMPTY) == 0)
		ipend |= SER_INT_RXREADY;

	uart_unlock(sc->sc_hwmtx);

	return (ipend);
}