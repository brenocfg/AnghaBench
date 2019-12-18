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
struct pci_driver {struct pci_device_id* id_table; } ;
struct pci_device_id {unsigned short vendor; unsigned short device; } ;
struct pci_dev {unsigned short vendor; unsigned short device; struct pci_driver* driver; } ;

/* Variables and functions */

__attribute__((used)) static bool match_id(struct pci_dev *pdev, unsigned short vendor, unsigned short device)
{
	struct pci_driver *drv = pdev->driver;
	const struct pci_device_id *id;

	if (pdev->vendor == vendor && pdev->device == device)
		return true;

	for (id = drv ? drv->id_table : NULL; id && id->vendor; id++)
		if (id->vendor == vendor && id->device == device)
			break;

	return id && id->vendor;
}