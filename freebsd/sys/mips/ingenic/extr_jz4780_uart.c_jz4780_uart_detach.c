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
struct jz4780_uart_softc {int /*<<< orphan*/ * clk_baud; int /*<<< orphan*/ * clk_mod; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 struct jz4780_uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int uart_bus_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_uart_detach(device_t dev)
{
	struct jz4780_uart_softc *sc;
	int rv;

	rv = uart_bus_detach(dev);
	if (rv != 0)
		return (rv);

	sc = device_get_softc(dev);
	if (sc->clk_mod != NULL) {
		clk_release(sc->clk_mod);
	}
	if (sc->clk_baud != NULL) {
		clk_release(sc->clk_baud);
	}
	return (0);
}