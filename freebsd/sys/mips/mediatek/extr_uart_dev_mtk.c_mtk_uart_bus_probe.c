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
struct uart_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int mtk_uart_probe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mtk_uart_bus_probe(struct uart_softc *sc)
{
	int error;

	error = mtk_uart_probe(&sc->sc_bas);
	if (error)
		return (error);
		
	device_set_desc(sc->sc_dev, "MTK UART Controller");

	return (0);
}