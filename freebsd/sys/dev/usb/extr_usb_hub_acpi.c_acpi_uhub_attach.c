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
struct acpi_uhub_softc {int /*<<< orphan*/ * ah; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int acpi_uhub_attach_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_uhub_detach (int /*<<< orphan*/ ) ; 
 struct acpi_uhub_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int uhub_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_uhub_attach(device_t dev)
{
	int ret;
	struct acpi_uhub_softc *sc = device_get_softc(dev);

	sc->ah = acpi_get_handle(dev);

	if (sc->ah == NULL) {
		return (ENXIO);
	}
	if ((ret = uhub_attach(dev)) != 0) {
		return (ret);
	}

	if ((ret = acpi_uhub_attach_common(dev)) != 0) {
		acpi_uhub_detach(dev);
	}

	return (ret);
}