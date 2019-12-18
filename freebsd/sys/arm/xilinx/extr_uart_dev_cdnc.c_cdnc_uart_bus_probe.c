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
struct uart_softc {int /*<<< orphan*/  sc_dev; scalar_t__ sc_hwoflow; scalar_t__ sc_hwiflow; void* sc_rxfifosz; void* sc_txfifosz; } ;

/* Variables and functions */
 void* UART_FIFO_SIZE ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

int
cdnc_uart_bus_probe(struct uart_softc *sc)
{

	sc->sc_txfifosz = UART_FIFO_SIZE;
	sc->sc_rxfifosz = UART_FIFO_SIZE;
	sc->sc_hwiflow = 0;
	sc->sc_hwoflow = 0;

	device_set_desc(sc->sc_dev, "Cadence UART");

	return (0);
}