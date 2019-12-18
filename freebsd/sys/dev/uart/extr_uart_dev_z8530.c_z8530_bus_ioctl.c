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
struct z8530_softc {int /*<<< orphan*/  tpc; } ;
struct uart_bas {int rclk; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RR_TCH ; 
 int /*<<< orphan*/  RR_TCL ; 
 int /*<<< orphan*/  TPC_BRK ; 
#define  UART_IOCTL_BAUD 129 
#define  UART_IOCTL_BREAK 128 
 int /*<<< orphan*/  WR_TPC ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getmreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setmreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
z8530_bus_ioctl(struct uart_softc *sc, int request, intptr_t data)
{
	struct z8530_softc *z8530 = (struct z8530_softc*)sc;
	struct uart_bas *bas;
	int baudrate, divisor, error;

	bas = &sc->sc_bas;
	error = 0;
	uart_lock(sc->sc_hwmtx);
	switch (request) {
	case UART_IOCTL_BREAK:
		if (data)
			z8530->tpc |= TPC_BRK;
		else
			z8530->tpc &= ~TPC_BRK;
		uart_setmreg(bas, WR_TPC, z8530->tpc);
		uart_barrier(bas);
		break;
	case UART_IOCTL_BAUD:
		divisor = uart_getmreg(bas, RR_TCH);
		divisor = (divisor << 8) | uart_getmreg(bas, RR_TCL);
		baudrate = bas->rclk / 2 / (divisor + 2);
		*(int*)data = baudrate;
		break;
	default:
		error = EINVAL;
		break;
	}
	uart_unlock(sc->sc_hwmtx);
	return (error);
}