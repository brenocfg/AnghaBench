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
struct uart_softc {int sc_rxfifosz; int sc_txfifosz; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int lowrisc_uart_probe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lowrisc_uart_bus_probe(struct uart_softc *sc)
{
	int error;

	error = lowrisc_uart_probe(&sc->sc_bas);
	if (error)
		return (error);

	/*
	 * On input we can read up to the full fifo size at once.  On output, we
	 * want to write only as much as the programmed tx low water level,
	 * because that's all we can be certain we have room for in the fifo
	 * when we get a tx-ready interrupt.
	 */
	sc->sc_rxfifosz = 2048;
	sc->sc_txfifosz = 2048;

	device_set_desc(sc->sc_dev, "lowRISC UART");

	return (0);
}