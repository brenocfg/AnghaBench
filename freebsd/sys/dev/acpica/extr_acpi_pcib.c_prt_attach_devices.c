#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_3__ {char* Source; int /*<<< orphan*/  Pin; int /*<<< orphan*/  Address; int /*<<< orphan*/  SourceIndex; } ;
typedef  TYPE_1__ ACPI_PCI_ROUTING_TABLE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  AcpiGetHandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acpi_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_pci_link_add_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prt_attach_devices(ACPI_PCI_ROUTING_TABLE *entry, void *arg)
{
    ACPI_HANDLE handle;
    device_t child, pcib;
    int error;

    /* We only care about entries that reference a link device. */
    if (entry->Source[0] == '\0')
	return;

    /*
     * In practice, we only see SourceIndex's of 0 out in the wild.
     * When indices != 0 have been found, they've been bugs in the ASL.
     */
    if (entry->SourceIndex != 0)
	return;

    /* Lookup the associated handle and device. */
    pcib = (device_t)arg;
    if (ACPI_FAILURE(AcpiGetHandle(ACPI_ROOT_OBJECT, entry->Source, &handle)))
	return;
    child = acpi_get_device(handle);
    if (child == NULL)
	return;

    /* If the device hasn't been probed yet, force it to do so. */
    error = device_probe_and_attach(child);
    if (error != 0) {
	device_printf(pcib, "failed to force attach of %s\n",
	    acpi_name(handle));
	return;
    }

    /* Add a reference for a specific bus/device/pin tuple. */
    acpi_pci_link_add_reference(child, entry->SourceIndex, pcib,
	ACPI_ADR_PCI_SLOT(entry->Address), entry->Pin);
}