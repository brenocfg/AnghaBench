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
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3 ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  AcpiFormatException (scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_pwr_switch_consumer (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ pci_do_power_resume ; 
 scalar_t__ pci_do_power_suspend ; 
 int pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_powerstate ; 
 int pci_set_powerstate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_pci_set_powerstate_method(device_t dev, device_t child, int state)
{
	ACPI_HANDLE h;
	ACPI_STATUS status;
	int old_state, error;

	error = 0;
	if (state < ACPI_STATE_D0 || state > ACPI_STATE_D3)
		return (EINVAL);

	/*
	 * We set the state using PCI Power Management outside of setting
	 * the ACPI state.  This means that when powering down a device, we
	 * first shut it down using PCI, and then using ACPI, which lets ACPI
	 * try to power down any Power Resources that are now no longer used.
	 * When powering up a device, we let ACPI set the state first so that
	 * it can enable any needed Power Resources before changing the PCI
	 * power state.
	 */
	ACPI_SERIAL_BEGIN(pci_powerstate);
	old_state = pci_get_powerstate(child);
	if (old_state < state && pci_do_power_suspend) {
		error = pci_set_powerstate_method(dev, child, state);
		if (error)
			goto out;
	}
	h = acpi_get_handle(child);
	status = acpi_pwr_switch_consumer(h, state);
	if (ACPI_SUCCESS(status)) {
		if (bootverbose)
			device_printf(dev, "set ACPI power state D%d on %s\n",
			    state, acpi_name(h));
	} else if (status != AE_NOT_FOUND)
		device_printf(dev,
		    "failed to set ACPI power state D%d on %s: %s\n",
		    state, acpi_name(h), AcpiFormatException(status));
	if (old_state > state && pci_do_power_resume)
		error = pci_set_powerstate_method(dev, child, state);

out:
	ACPI_SERIAL_END(pci_powerstate);
	return (error);
}