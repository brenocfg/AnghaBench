#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int Flags; } ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;
typedef  TYPE_1__ ACPI_DEVICE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_PCI_ROOT_BRIDGE ; 
 int /*<<< orphan*/  AcpiGetObjectInfo (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_1__*) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_cfgregopen () ; 

__attribute__((used)) static int
acpi_pcib_acpi_probe(device_t dev)
{
    ACPI_DEVICE_INFO	*devinfo;
    ACPI_HANDLE		h;
    int			root;

    if (acpi_disabled("pcib") || (h = acpi_get_handle(dev)) == NULL ||
	ACPI_FAILURE(AcpiGetObjectInfo(h, &devinfo)))
	return (ENXIO);
    root = (devinfo->Flags & ACPI_PCI_ROOT_BRIDGE) != 0;
    AcpiOsFree(devinfo);
    if (!root || pci_cfgregopen() == 0)
	return (ENXIO);

    device_set_desc(dev, "ACPI Host-PCI bridge");
    return (0);
}