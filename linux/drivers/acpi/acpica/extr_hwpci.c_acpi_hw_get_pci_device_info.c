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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  void* u16 ;
struct acpi_pci_id {void* bus; int /*<<< orphan*/  function; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_object_type ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_LODWORD (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  METHOD_NAME__ADR ; 
 int /*<<< orphan*/  PCI_CFG_HEADER_TYPE_REG ; 
 int /*<<< orphan*/  PCI_CFG_PRIMARY_BUS_NUMBER_REG ; 
 int /*<<< orphan*/  PCI_CFG_SECONDARY_BUS_NUMBER_REG ; 
 scalar_t__ PCI_HEADER_TYPE_MASK ; 
 scalar_t__ PCI_TYPE_BRIDGE ; 
 scalar_t__ PCI_TYPE_CARDBUS_BRIDGE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  acpi_get_type (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_os_read_pci_configuration (struct acpi_pci_id*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  acpi_ut_evaluate_numeric_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static acpi_status
acpi_hw_get_pci_device_info(struct acpi_pci_id *pci_id,
			    acpi_handle pci_device,
			    u16 *bus_number, u8 *is_bridge)
{
	acpi_status status;
	acpi_object_type object_type;
	u64 return_value;
	u64 pci_value;

	/* We only care about objects of type Device */

	status = acpi_get_type(pci_device, &object_type);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	if (object_type != ACPI_TYPE_DEVICE) {
		return (AE_OK);
	}

	/* We need an _ADR. Ignore device if not present */

	status = acpi_ut_evaluate_numeric_object(METHOD_NAME__ADR,
						 pci_device, &return_value);
	if (ACPI_FAILURE(status)) {
		return (AE_OK);
	}

	/*
	 * From _ADR, get the PCI Device and Function and
	 * update the PCI ID.
	 */
	pci_id->device = ACPI_HIWORD(ACPI_LODWORD(return_value));
	pci_id->function = ACPI_LOWORD(ACPI_LODWORD(return_value));

	/*
	 * If the previous device was a bridge, use the previous
	 * device bus number
	 */
	if (*is_bridge) {
		pci_id->bus = *bus_number;
	}

	/*
	 * Get the bus numbers from PCI Config space:
	 *
	 * First, get the PCI header_type
	 */
	*is_bridge = FALSE;
	status = acpi_os_read_pci_configuration(pci_id,
						PCI_CFG_HEADER_TYPE_REG,
						&pci_value, 8);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* We only care about bridges (1=pci_bridge, 2=card_bus_bridge) */

	pci_value &= PCI_HEADER_TYPE_MASK;

	if ((pci_value != PCI_TYPE_BRIDGE) &&
	    (pci_value != PCI_TYPE_CARDBUS_BRIDGE)) {
		return (AE_OK);
	}

	/* Bridge: Get the Primary bus_number */

	status = acpi_os_read_pci_configuration(pci_id,
						PCI_CFG_PRIMARY_BUS_NUMBER_REG,
						&pci_value, 8);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	*is_bridge = TRUE;
	pci_id->bus = (u16)pci_value;

	/* Bridge: Get the Secondary bus_number */

	status = acpi_os_read_pci_configuration(pci_id,
						PCI_CFG_SECONDARY_BUS_NUMBER_REG,
						&pci_value, 8);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	*bus_number = (u16)pci_value;
	return (AE_OK);
}