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
typedef  int uint16_t ;
struct uart_bas {scalar_t__ chan; } ;
struct uart_softc {struct uart_devinfo* sc_sysdev; struct uart_bas sc_bas; } ;
struct uart_devinfo {int /*<<< orphan*/  parity; int /*<<< orphan*/  stopbits; int /*<<< orphan*/  databits; int /*<<< orphan*/  baudrate; } ;

/* Variables and functions */
 int QUICC_PRAM_SCC_RBASE (scalar_t__) ; 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 int /*<<< orphan*/  quicc_bus_getsig (struct uart_softc*) ; 
 int /*<<< orphan*/  quicc_param (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int quicc_read2 (struct uart_bas*,int) ; 
 int /*<<< orphan*/  quicc_setup (struct uart_bas*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicc_write2 (struct uart_bas*,int,int) ; 

__attribute__((used)) static int
quicc_bus_attach(struct uart_softc *sc)
{
	struct uart_bas *bas;
	struct uart_devinfo *di;
	uint16_t st, rb;

	bas = &sc->sc_bas;
	if (sc->sc_sysdev != NULL) {
		di = sc->sc_sysdev;
		quicc_param(bas, di->baudrate, di->databits, di->stopbits,
		    di->parity);
	} else {
		quicc_setup(bas, 9600, 8, 1, UART_PARITY_NONE);
	}

	/* Enable interrupts on the receive buffer. */
	rb = quicc_read2(bas, QUICC_PRAM_SCC_RBASE(bas->chan - 1));
	st = quicc_read2(bas, rb);
	quicc_write2(bas, rb, st | 0x9000);

	(void)quicc_bus_getsig(sc);

	return (0);
}