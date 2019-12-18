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
struct mrsas_ident {scalar_t__ vendor; scalar_t__ device; int subvendor; int subdevice; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct mrsas_ident* device_table ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mrsas_ident *
mrsas_find_ident(device_t dev)
{
	struct mrsas_ident *pci_device;

	for (pci_device = device_table; pci_device->vendor != 0; pci_device++) {
		if ((pci_device->vendor == pci_get_vendor(dev)) &&
		    (pci_device->device == pci_get_device(dev)) &&
		    ((pci_device->subvendor == pci_get_subvendor(dev)) ||
		    (pci_device->subvendor == 0xffff)) &&
		    ((pci_device->subdevice == pci_get_subdevice(dev)) ||
		    (pci_device->subdevice == 0xffff)))
			return (pci_device);
	}
	return (NULL);
}