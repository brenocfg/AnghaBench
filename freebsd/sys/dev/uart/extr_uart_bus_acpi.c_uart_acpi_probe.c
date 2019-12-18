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
struct uart_softc {int /*<<< orphan*/  sc_class; } ;
struct acpi_uart_compat_data {int /*<<< orphan*/  cd_quirks; int /*<<< orphan*/  cd_rclk; int /*<<< orphan*/  cd_regiowidth; int /*<<< orphan*/  cd_regshft; int /*<<< orphan*/ * cd_desc; int /*<<< orphan*/  cd_class; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct acpi_uart_compat_data* uart_acpi_find_device (int /*<<< orphan*/ ) ; 
 int uart_bus_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_acpi_probe(device_t dev)
{
	struct uart_softc *sc;
	struct acpi_uart_compat_data *cd;

	sc = device_get_softc(dev);

	if ((cd = uart_acpi_find_device(dev)) != NULL) {
		sc->sc_class = cd->cd_class;
		if (cd->cd_desc != NULL)
			device_set_desc(dev, cd->cd_desc);
		return (uart_bus_probe(dev, cd->cd_regshft, cd->cd_regiowidth,
		    cd->cd_rclk, 0, 0, cd->cd_quirks));
	}
	return (ENXIO);
}