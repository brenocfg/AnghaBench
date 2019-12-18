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
struct uart_bas {int rclk; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int CCR_BAUDRATE_DIV ; 
 int CTRL_SND_BRK_SEQ ; 
 int ENOTTY ; 
 int /*<<< orphan*/  UART_CCR ; 
 int /*<<< orphan*/  UART_CTRL ; 
#define  UART_IOCTL_BAUD 129 
#define  UART_IOCTL_BREAK 128 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_mvebu_bus_ioctl(struct uart_softc *sc, int request, intptr_t data)
{
	struct uart_bas *bas;
	int ctrl, ret = 0;
	int divisor, baudrate;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	switch (request) {
	case UART_IOCTL_BREAK:
		ctrl = uart_getreg(bas, UART_CTRL);
		if (data)
			ctrl |= CTRL_SND_BRK_SEQ;
		else
			ctrl &=~ CTRL_SND_BRK_SEQ;
		uart_setreg(bas, UART_CTRL, ctrl);
		uart_barrier(bas);
		break;

	case UART_IOCTL_BAUD:
		divisor = uart_getreg(bas, UART_CCR) & CCR_BAUDRATE_DIV;
		baudrate = bas->rclk/(divisor * 16);
		*(int *)data = baudrate;
		break;

	default:
		ret = ENOTTY;
		break;
	}
	uart_unlock(sc->sc_hwmtx);

	return (ret);
}