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
struct acpi_prw_data {int /*<<< orphan*/  gpe_bit; int /*<<< orphan*/  gpe_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_FLAG_WAKE_ENABLED ; 
 int /*<<< orphan*/  ACPI_GPE_DISABLE ; 
 int /*<<< orphan*/  ACPI_GPE_ENABLE ; 
 int /*<<< orphan*/  AcpiSetGpeWakeMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int acpi_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_parse_prw (int /*<<< orphan*/ ,struct acpi_prw_data*) ; 
 int /*<<< orphan*/  acpi_set_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
acpi_wake_set_enable(device_t dev, int enable)
{
    struct acpi_prw_data prw;
    ACPI_STATUS status;
    int flags;

    /* Make sure the device supports waking the system and get the GPE. */
    if (acpi_parse_prw(acpi_get_handle(dev), &prw) != 0)
	return (ENXIO);

    flags = acpi_get_flags(dev);
    if (enable) {
	status = AcpiSetGpeWakeMask(prw.gpe_handle, prw.gpe_bit,
	    ACPI_GPE_ENABLE);
	if (ACPI_FAILURE(status)) {
	    device_printf(dev, "enable wake failed\n");
	    return (ENXIO);
	}
	acpi_set_flags(dev, flags | ACPI_FLAG_WAKE_ENABLED);
    } else {
	status = AcpiSetGpeWakeMask(prw.gpe_handle, prw.gpe_bit,
	    ACPI_GPE_DISABLE);
	if (ACPI_FAILURE(status)) {
	    device_printf(dev, "disable wake failed\n");
	    return (ENXIO);
	}
	acpi_set_flags(dev, flags & ~ACPI_FLAG_WAKE_ENABLED);
    }

    return (0);
}