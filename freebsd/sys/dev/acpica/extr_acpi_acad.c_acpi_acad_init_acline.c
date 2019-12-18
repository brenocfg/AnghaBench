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
struct acpi_acad_softc {int status; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ACPI_ACAD_RETRY_MAX ; 
 int /*<<< orphan*/  ACPI_VPRINT (scalar_t__,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  AcpiOsSleep (int) ; 
 int /*<<< orphan*/  acpi_acad_get_status (scalar_t__) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (scalar_t__) ; 
 struct acpi_acad_softc* device_get_softc (scalar_t__) ; 

__attribute__((used)) static void
acpi_acad_init_acline(void *arg)
{
    struct acpi_acad_softc *sc;
    device_t	dev;
    int		retry;

    dev = (device_t)arg;
    sc = device_get_softc(dev);
    ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		"acline initialization start\n");

    for (retry = 0; retry < ACPI_ACAD_RETRY_MAX; retry++) {
	acpi_acad_get_status(dev);
	if (sc->status != -1)
	    break;
	AcpiOsSleep(10000);
    }

    ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		"acline initialization done, tried %d times\n", retry + 1);
}