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
struct dmar_unit {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  ACPI_DMAR_PCI_PATH ;

/* Variables and functions */
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 struct dmar_unit* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int dmar_dev_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmar_dev_path (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int) ; 
 int dmar_devcnt ; 
 int /*<<< orphan*/ ** dmar_devs ; 
 scalar_t__ dmar_match_by_path (struct dmar_unit*,int,int,int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/  dmar_print_path (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ *) ; 
 int pci_get_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

struct dmar_unit *
dmar_find(device_t dev, bool verbose)
{
	device_t dmar_dev;
	struct dmar_unit *unit;
	const char *banner;
	int i, dev_domain, dev_busno, dev_path_len;

	/*
	 * This function can only handle PCI(e) devices.
	 */
	if (device_get_devclass(device_get_parent(dev)) !=
	    devclass_find("pci"))
		return (NULL);

	dmar_dev = NULL;
	dev_domain = pci_get_domain(dev);
	dev_path_len = dmar_dev_depth(dev);
	ACPI_DMAR_PCI_PATH dev_path[dev_path_len];
	dmar_dev_path(dev, &dev_busno, dev_path, dev_path_len);
	banner = "";

	for (i = 0; i < dmar_devcnt; i++) {
		if (dmar_devs[i] == NULL)
			continue;
		unit = device_get_softc(dmar_devs[i]);
		if (dmar_match_by_path(unit, dev_domain, dev_busno,
		    dev_path, dev_path_len, &banner))
			break;
	}
	if (i == dmar_devcnt)
		return (NULL);

	if (verbose) {
		device_printf(dev, "pci%d:%d:%d:%d matched dmar%d by %s",
		    dev_domain, pci_get_bus(dev), pci_get_slot(dev),
		    pci_get_function(dev), unit->unit, banner);
		printf(" scope path ");
		dmar_print_path(dev_busno, dev_path_len, dev_path);
		printf("\n");
	}
	return (unit);
}