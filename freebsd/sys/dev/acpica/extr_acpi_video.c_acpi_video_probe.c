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
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AcpiGetHandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiGetType (int /*<<< orphan*/ ,scalar_t__*) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
acpi_video_probe(device_t dev)
{
	ACPI_HANDLE devh, h;
	ACPI_OBJECT_TYPE t_dos;

	devh = acpi_get_handle(dev);
	if (acpi_disabled("video") ||
	    ACPI_FAILURE(AcpiGetHandle(devh, "_DOD", &h)) ||
	    ACPI_FAILURE(AcpiGetHandle(devh, "_DOS", &h)) ||
	    ACPI_FAILURE(AcpiGetType(h, &t_dos)) ||
	    t_dos != ACPI_TYPE_METHOD)
		return (ENXIO);

	device_set_desc(dev, "ACPI video extension");
	return (0);
}