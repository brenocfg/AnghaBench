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
typedef  int /*<<< orphan*/  uint8_t ;
struct uart_bas {int dummy; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SAB_DAFO ; 
 int /*<<< orphan*/  SAB_DAFO_XBRK ; 
 int /*<<< orphan*/  SAB_MODE ; 
 int /*<<< orphan*/  SAB_MODE_FCTS ; 
 int /*<<< orphan*/  SAB_MODE_FRTS ; 
 int /*<<< orphan*/  SAB_MODE_RTS ; 
#define  UART_IOCTL_BREAK 130 
#define  UART_IOCTL_IFLOW 129 
#define  UART_IOCTL_OFLOW 128 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sab82532_bus_ioctl(struct uart_softc *sc, int request, intptr_t data)
{
	struct uart_bas *bas;
	uint8_t dafo, mode;
	int error;

	bas = &sc->sc_bas;
	error = 0;
	uart_lock(sc->sc_hwmtx);
	switch (request) {
	case UART_IOCTL_BREAK:
		dafo = uart_getreg(bas, SAB_DAFO);
		if (data)
			dafo |= SAB_DAFO_XBRK;
		else
			dafo &= ~SAB_DAFO_XBRK;
		uart_setreg(bas, SAB_DAFO, dafo);
		uart_barrier(bas);
		break;
	case UART_IOCTL_IFLOW:
		mode = uart_getreg(bas, SAB_MODE);
		if (data) {
			mode &= ~SAB_MODE_RTS;
			mode |= SAB_MODE_FRTS;
		} else {
			mode |= SAB_MODE_RTS;
			mode &= ~SAB_MODE_FRTS;
		}
		uart_setreg(bas, SAB_MODE, mode);
		uart_barrier(bas);
		break;
	case UART_IOCTL_OFLOW:
		mode = uart_getreg(bas, SAB_MODE);
		if (data)
			mode &= ~SAB_MODE_FCTS;
		else
			mode |= SAB_MODE_FCTS;
		uart_setreg(bas, SAB_MODE, mode);
		uart_barrier(bas);
		break;
	default:
		error = EINVAL;
		break;
	}
	uart_unlock(sc->sc_hwmtx);
	return (error);
}