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
struct uart_devinfo {int /*<<< orphan*/  parity; int /*<<< orphan*/  stopbits; int /*<<< orphan*/  databits; int /*<<< orphan*/  baudrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNC_UART_IEN_REG ; 
 int CDNC_UART_INT_DMSI ; 
 int CDNC_UART_INT_RXOVR ; 
 int CDNC_UART_INT_RXTMOUT ; 
 int CDNC_UART_INT_RXTRIG ; 
 int CDNC_UART_INT_TXOVR ; 
 int /*<<< orphan*/  WR4 (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdnc_uart_bus_getsig (struct uart_softc*) ; 
 int /*<<< orphan*/  cdnc_uart_hw_init (struct uart_bas*) ; 
 int /*<<< orphan*/  cdnc_uart_set_params (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdnc_uart_bus_attach(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	struct uart_devinfo *di;

	if (sc->sc_sysdev != NULL) {
		di = sc->sc_sysdev;
		(void)cdnc_uart_set_params(bas, di->baudrate, di->databits,
					   di->stopbits, di->parity);
	} else
		cdnc_uart_hw_init(bas);

	(void)cdnc_uart_bus_getsig(sc);

	/* Enable interrupts. */
	WR4(bas, CDNC_UART_IEN_REG,
	    CDNC_UART_INT_RXTRIG | CDNC_UART_INT_RXTMOUT |
	    CDNC_UART_INT_TXOVR | CDNC_UART_INT_RXOVR |
	    CDNC_UART_INT_DMSI);

	return (0);
}