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
typedef  scalar_t__ uint16_t ;
struct imcsmb_pci_device {scalar_t__ id; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ PCI_VENDOR_INTEL ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct imcsmb_pci_device* imcsmb_pci_devices ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imcsmb_pci_probe(device_t dev)
{
	struct imcsmb_pci_device *pci_device;
	int rc;
	uint16_t pci_dev_id;

	rc = ENXIO;

	if (pci_get_vendor(dev) != PCI_VENDOR_INTEL) {
		goto out;
	}

	pci_dev_id = pci_get_device(dev);
	for (pci_device = imcsmb_pci_devices;
	    pci_device->name != NULL;
	    pci_device++) {
		if (pci_dev_id == pci_device->id) {
			device_set_desc(dev, pci_device->name);
			rc = BUS_PROBE_DEFAULT;
			goto out;
		}
	}

out:
	return (rc);
}