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
struct uart_softc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  UART_IOCTL_BAUD 131 
#define  UART_IOCTL_BREAK 130 
#define  UART_IOCTL_IFLOW 129 
#define  UART_IOCTL_OFLOW 128 

__attribute__((used)) static int
ar933x_bus_ioctl(struct uart_softc *sc, int request, intptr_t data)
{
	int error = 0;

	/* XXX lock */
	switch (request) {
	case UART_IOCTL_BREAK:
	case UART_IOCTL_IFLOW:
	case UART_IOCTL_OFLOW:
		break;
	case UART_IOCTL_BAUD:
		*(int*)data = 115200;
		break;
	default:
		error = EINVAL;
		break;
	}

	/* XXX unlock */

	return (error);
}