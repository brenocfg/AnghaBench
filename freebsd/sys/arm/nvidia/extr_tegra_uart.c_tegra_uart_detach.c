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
struct tegra_softc {int /*<<< orphan*/ * clk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 struct tegra_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int uart_bus_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_uart_detach(device_t dev)
{
	struct tegra_softc *sc;

	sc = device_get_softc(dev);
	if (sc->clk != NULL) {
		clk_release(sc->clk);
	}

	return (uart_bus_detach(dev));
}