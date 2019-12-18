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
struct pci_devinfo {int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCI_DOMAINMAX ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 struct pci_devinfo* pci_read_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vmd_bus_detach(device_t dev)
{
	struct pci_devinfo *dinfo;
	int b, s, f;

	device_delete_children(dev);

	b = s = f = 0;
	dinfo = pci_read_device(device_get_parent(dev), dev,
	    PCI_DOMAINMAX - device_get_unit(device_get_parent(dev)),
	    b, s, f);
	if (dinfo == NULL) {
		resource_list_free(&dinfo->resources);
	}
	return (0);
}