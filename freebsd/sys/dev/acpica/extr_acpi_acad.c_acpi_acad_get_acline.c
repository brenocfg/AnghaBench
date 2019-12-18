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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  acpi_acad_devclass ; 
 int /*<<< orphan*/  acpi_acad_get_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_acad_softc* device_get_softc (int /*<<< orphan*/ *) ; 

int
acpi_acad_get_acline(int *status)
{
    struct acpi_acad_softc *sc;
    device_t dev;

    dev = devclass_get_device(acpi_acad_devclass, 0);
    if (dev == NULL)
	return (ENXIO);
    sc = device_get_softc(dev);

    acpi_acad_get_status(dev);
    *status = sc->status;

    return (0);
}