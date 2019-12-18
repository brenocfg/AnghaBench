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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  descr ;

/* Variables and functions */
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_short_name (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_link_ids ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
acpi_pci_link_probe(device_t dev)
{
	char descr[28], name[12];
	int rv;

	/*
	 * We explicitly do not check _STA since not all systems set it to
	 * sensible values.
	 */
	if (acpi_disabled("pci_link"))
	    return (ENXIO);
	rv = ACPI_ID_PROBE(device_get_parent(dev), dev, pci_link_ids, NULL);
	if (rv > 0)
	  return (rv);
	
	if (ACPI_SUCCESS(acpi_short_name(acpi_get_handle(dev), name,
	    sizeof(name)))) {
		snprintf(descr, sizeof(descr), "ACPI PCI Link %s", name);
		device_set_desc_copy(dev, descr);
	} else
		device_set_desc(dev, "ACPI PCI Link");
	device_quiet(dev);
	return (rv);
}