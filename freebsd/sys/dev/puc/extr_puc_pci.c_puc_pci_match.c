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
struct puc_cfg {int vendor; scalar_t__ device; scalar_t__ subvendor; scalar_t__ subdevice; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subvendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct puc_cfg *
puc_pci_match(device_t dev, const struct puc_cfg *desc)
{
	uint16_t vendor, device;
	uint16_t subvendor, subdevice;

	vendor = pci_get_vendor(dev);
	device = pci_get_device(dev);
	subvendor = pci_get_subvendor(dev);
	subdevice = pci_get_subdevice(dev);

	while (desc->vendor != 0xffff) {
		if (desc->vendor == vendor && desc->device == device) {
			/* exact match */
			if (desc->subvendor == subvendor &&
		            desc->subdevice == subdevice)
				return (desc);
			/* wildcard match */
			if (desc->subvendor == 0xffff)
				return (desc);
		}
		desc++;
	}

	/* no match */
	return (NULL);
}