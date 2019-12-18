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
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int ACPI_FLAG_WAKE_ENABLED ; 
 int /*<<< orphan*/  ACPI_GPE_DISABLE ; 
 int /*<<< orphan*/  AcpiSetGpeWakeMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ acpi_get_device (int /*<<< orphan*/ ) ; 
 int acpi_get_flags (scalar_t__) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_parse_prw (int /*<<< orphan*/ ,struct acpi_prw_data*) ; 
 int /*<<< orphan*/  acpi_pwr_wake_enable (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_wake_sleep_prep(ACPI_HANDLE handle, int sstate)
{
    struct acpi_prw_data prw;
    device_t dev;

    /* Check that this is a wake-capable device and get its GPE. */
    if (acpi_parse_prw(handle, &prw) != 0)
	return (ENXIO);
    dev = acpi_get_device(handle);

    /*
     * The destination sleep state must be less than (i.e., higher power)
     * or equal to the value specified by _PRW.  If this GPE cannot be
     * enabled for the next sleep state, then disable it.  If it can and
     * the user requested it be enabled, turn on any required power resources
     * and set _PSW.
     */
    if (sstate > prw.lowest_wake) {
	AcpiSetGpeWakeMask(prw.gpe_handle, prw.gpe_bit, ACPI_GPE_DISABLE);
	if (bootverbose)
	    device_printf(dev, "wake_prep disabled wake for %s (S%d)\n",
		acpi_name(handle), sstate);
    } else if (dev && (acpi_get_flags(dev) & ACPI_FLAG_WAKE_ENABLED) != 0) {
	acpi_pwr_wake_enable(handle, 1);
	acpi_SetInteger(handle, "_PSW", 1);
	if (bootverbose)
	    device_printf(dev, "wake_prep enabled for %s (S%d)\n",
		acpi_name(handle), sstate);
    }

    return (0);
}