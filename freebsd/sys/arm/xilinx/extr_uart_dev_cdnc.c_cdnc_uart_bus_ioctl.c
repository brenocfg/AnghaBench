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
 int /*<<< orphan*/  CDNC_UART_CTRL_REG ; 
 int /*<<< orphan*/  CDNC_UART_CTRL_REG_STARTBRK ; 
 int /*<<< orphan*/  CDNC_UART_CTRL_REG_STOPBRK ; 
 int /*<<< orphan*/  CDNC_UART_MODEM_CTRL_REG ; 
 int /*<<< orphan*/  CDNC_UART_MODEM_CTRL_REG_RTS ; 
 int EINVAL ; 
 int /*<<< orphan*/  RD4 (struct uart_bas*,int /*<<< orphan*/ ) ; 
#define  UART_IOCTL_BREAK 129 
#define  UART_IOCTL_IFLOW 128 
 int /*<<< orphan*/  WR4 (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdnc_uart_bus_ioctl(struct uart_softc *sc, int request, intptr_t data)
{
	struct uart_bas *bas = &sc->sc_bas;
	uint32_t uart_ctrl, modem_ctrl;
	int error = 0;

	uart_lock(sc->sc_hwmtx);

	switch (request) {
	case UART_IOCTL_BREAK:
		uart_ctrl = RD4(bas, CDNC_UART_CTRL_REG);
		if (data) {
			uart_ctrl |= CDNC_UART_CTRL_REG_STARTBRK;
			uart_ctrl &= ~CDNC_UART_CTRL_REG_STOPBRK;
		} else {
			uart_ctrl |= CDNC_UART_CTRL_REG_STOPBRK;
			uart_ctrl &= ~CDNC_UART_CTRL_REG_STARTBRK;
		}
		WR4(bas, CDNC_UART_CTRL_REG, uart_ctrl);
		break;
	case UART_IOCTL_IFLOW:
		modem_ctrl = RD4(bas, CDNC_UART_MODEM_CTRL_REG);
		if (data)
			modem_ctrl |= CDNC_UART_MODEM_CTRL_REG_RTS;
		else
			modem_ctrl &= ~CDNC_UART_MODEM_CTRL_REG_RTS;
		WR4(bas, CDNC_UART_MODEM_CTRL_REG, modem_ctrl);
		break;
	default:
		error = EINVAL;
		break;
	}

	uart_unlock(sc->sc_hwmtx);

	return (error);
}