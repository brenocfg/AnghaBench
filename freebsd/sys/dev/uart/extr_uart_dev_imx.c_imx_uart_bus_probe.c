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
struct uart_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_txfifosz; int /*<<< orphan*/  sc_rxfifosz; int /*<<< orphan*/  sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_FIFOSZ ; 
 int /*<<< orphan*/  IMX_TXFIFO_LEVEL ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int imx_uart_probe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imx_uart_bus_probe(struct uart_softc *sc)
{
	int error;

	error = imx_uart_probe(&sc->sc_bas);
	if (error)
		return (error);

	/*
	 * On input we can read up to the full fifo size at once.  On output, we
	 * want to write only as much as the programmed tx low water level,
	 * because that's all we can be certain we have room for in the fifo
	 * when we get a tx-ready interrupt.
	 */
	sc->sc_rxfifosz = IMX_FIFOSZ;
	sc->sc_txfifosz = IMX_TXFIFO_LEVEL;

	device_set_desc(sc->sc_dev, "Freescale i.MX UART");
	return (0);
}