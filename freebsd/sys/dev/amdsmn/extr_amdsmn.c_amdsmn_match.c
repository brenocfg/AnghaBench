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
struct pciid {scalar_t__ amdsmn_vendorid; scalar_t__ amdsmn_deviceid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pciid* amdsmn_ids ; 
 size_t nitems (struct pciid*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
amdsmn_match(device_t parent, const struct pciid **pciid_out)
{
	uint16_t vendor, device;
	size_t i;

	vendor = pci_get_vendor(parent);
	device = pci_get_device(parent);

	for (i = 0; i < nitems(amdsmn_ids); i++) {
		if (vendor == amdsmn_ids[i].amdsmn_vendorid &&
		    device == amdsmn_ids[i].amdsmn_deviceid) {
			if (pciid_out != NULL)
				*pciid_out = &amdsmn_ids[i];
			return (true);
		}
	}
	return (false);
}