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
struct acpi_prw_data {int lowest_wake; int /*<<< orphan*/  gpe_bit; int /*<<< orphan*/  gpe_handle; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int ACPI_FLAG_WAKE_ENABLED ; 
 int /*<<< orphan*/  ACPI_GPE_ENABLE ; 
 int /*<<< orphan*/  AcpiSetGpeWakeMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * acpi_get_device (int /*<<< orphan*/ ) ; 
 int acpi_get_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_parse_prw (int /*<<< orphan*/ ,struct acpi_prw_data*) ; 
 int /*<<< orphan*/  acpi_pwr_wake_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_wake_run_prep(ACPI_HANDLE handle, int sstate)
{
    struct acpi_prw_data prw;
    device_t dev;

    /*
     * Check that this is a wake-capable device and get its GPE.  Return
     * now if the user didn't enable this device for wake.
     */
    if (acpi_parse_prw(handle, &prw) != 0)
	return (ENXIO);
    dev = acpi_get_device(handle);
    if (dev == NULL || (acpi_get_flags(dev) & ACPI_FLAG_WAKE_ENABLED) == 0)
	return (0);

    /*
     * If this GPE couldn't be enabled for the previous sleep state, it was
     * disabled before going to sleep so re-enable it.  If it was enabled,
     * clear _PSW and turn off any power resources it used.
     */
    if (sstate > prw.lowest_wake) {
	AcpiSetGpeWakeMask(prw.gpe_handle, prw.gpe_bit, ACPI_GPE_ENABLE);
	if (bootverbose)
	    device_printf(dev, "run_prep re-enabled %s\n", acpi_name(handle));
    } else {
	acpi_SetInteger(handle, "_PSW", 0);
	acpi_pwr_wake_enable(handle, 0);
	if (bootverbose)
	    device_printf(dev, "run_prep cleaned up for %s\n",
		acpi_name(handle));
    }

    return (0);
}