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
struct ichsmb_device {scalar_t__ id; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCI_VENDOR_INTEL ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ichsmb_device* ichsmb_devices ; 
 int ichsmb_probe (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ichsmb_pci_probe(device_t dev)
{
	const struct ichsmb_device *device;

	if (pci_get_vendor(dev) != PCI_VENDOR_INTEL)
		return (ENXIO);

	for (device = ichsmb_devices; device->name != NULL; device++) {
		if (pci_get_device(dev) == device->id) {
			device_set_desc(dev, device->name);
			return (ichsmb_probe(dev));
		}
	}

	return (ENXIO);
}