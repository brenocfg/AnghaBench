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

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_PCI ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_cfgregopen () ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_pcib_pci_probe(device_t dev)
{

    if (pci_get_class(dev) != PCIC_BRIDGE ||
	pci_get_subclass(dev) != PCIS_BRIDGE_PCI ||
	acpi_disabled("pci"))
	return (ENXIO);
    if (acpi_get_handle(dev) == NULL)
	return (ENXIO);
    if (pci_cfgregopen() == 0)
	return (ENXIO);

    device_set_desc(dev, "ACPI PCI-PCI bridge");
    return (-1000);
}