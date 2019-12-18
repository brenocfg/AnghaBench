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
struct uart_bas {int dummy; } ;
struct uart_softc {struct uart_devinfo* sc_sysdev; struct uart_bas sc_bas; } ;
struct uart_devinfo {int databits; int stopbits; int /*<<< orphan*/  parity; int /*<<< orphan*/  baudrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BAUD_RATE ; 
 int /*<<< orphan*/  lowrisc_uart_bus_getsig (struct uart_softc*) ; 
 int /*<<< orphan*/  lowrisc_uart_init (struct uart_bas*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lowrisc_uart_bus_attach(struct uart_softc *sc)
{
	struct uart_bas *bas;
	struct uart_devinfo *di;

	bas = &sc->sc_bas;
	if (sc->sc_sysdev != NULL) {
		di = sc->sc_sysdev;
		lowrisc_uart_init(bas, di->baudrate, di->databits, di->stopbits,
		    di->parity);
	} else
		lowrisc_uart_init(bas, DEFAULT_BAUD_RATE, 8, 1, 0);

	(void)lowrisc_uart_bus_getsig(sc);

	/* TODO: clear all pending interrupts. */

	return (0);
}