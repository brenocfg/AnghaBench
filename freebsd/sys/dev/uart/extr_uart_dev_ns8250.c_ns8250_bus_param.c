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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct ns8250_softc {scalar_t__ busy_detect; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DW_REG_USR ; 
 int EIO ; 
 int USR_BUSY ; 
 int ns8250_param (struct uart_bas*,int,int,int,int) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

int
ns8250_bus_param(struct uart_softc *sc, int baudrate, int databits,
    int stopbits, int parity)
{
	struct ns8250_softc *ns8250;
	struct uart_bas *bas;
	int error, limit;

	ns8250 = (struct ns8250_softc*)sc;
	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	/*
	 * When using DW UART with BUSY detection it is necessary to wait
	 * until all serial transfers are finished before manipulating the
	 * line control. LCR will not be affected when UART is busy.
	 */
	if (ns8250->busy_detect != 0) {
		/*
		 * Pick an arbitrary high limit to avoid getting stuck in
		 * an infinite loop in case when the hardware is broken.
		 */
		limit = 10 * 1024;
		while (((uart_getreg(bas, DW_REG_USR) & USR_BUSY) != 0) &&
		    --limit)
			DELAY(4);

		if (limit <= 0) {
			/* UART appears to be stuck */
			uart_unlock(sc->sc_hwmtx);
			return (EIO);
		}
	}

	error = ns8250_param(bas, baudrate, databits, stopbits, parity);
	uart_unlock(sc->sc_hwmtx);
	return (error);
}