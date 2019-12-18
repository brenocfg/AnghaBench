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
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ VIRTIO_PCI_ABI_VERSION ; 
 scalar_t__ VIRTIO_PCI_DEVICEID_MAX ; 
 scalar_t__ VIRTIO_PCI_DEVICEID_MIN ; 
 scalar_t__ VIRTIO_PCI_VENDORID ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_revid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* virtio_device_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtpci_probe(device_t dev)
{
	char desc[36];
	const char *name;

	if (pci_get_vendor(dev) != VIRTIO_PCI_VENDORID)
		return (ENXIO);

	if (pci_get_device(dev) < VIRTIO_PCI_DEVICEID_MIN ||
	    pci_get_device(dev) > VIRTIO_PCI_DEVICEID_MAX)
		return (ENXIO);

	if (pci_get_revid(dev) != VIRTIO_PCI_ABI_VERSION)
		return (ENXIO);

	name = virtio_device_name(pci_get_subdevice(dev));
	if (name == NULL)
		name = "Unknown";

	snprintf(desc, sizeof(desc), "VirtIO PCI %s adapter", name);
	device_set_desc_copy(dev, desc);

	return (BUS_PROBE_DEFAULT);
}