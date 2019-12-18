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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/  sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 
 int z8530_param (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
z8530_bus_param(struct uart_softc *sc, int baudrate, int databits,
    int stopbits, int parity)
{
	struct z8530_softc *z8530 = (struct z8530_softc*)sc;
	int error;

	uart_lock(sc->sc_hwmtx);
	error = z8530_param(&sc->sc_bas, baudrate, databits, stopbits, parity,
	    &z8530->tpc);
	uart_unlock(sc->sc_hwmtx);
	return (error);
}