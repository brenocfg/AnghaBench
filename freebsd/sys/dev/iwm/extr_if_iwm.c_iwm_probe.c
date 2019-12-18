#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {scalar_t__ device; TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ PCI_VENDOR_INTEL ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* iwm_devices ; 
 int nitems (TYPE_2__*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwm_probe(device_t dev)
{
	int i;

	for (i = 0; i < nitems(iwm_devices); i++) {
		if (pci_get_vendor(dev) == PCI_VENDOR_INTEL &&
		    pci_get_device(dev) == iwm_devices[i].device) {
			device_set_desc(dev, iwm_devices[i].cfg->name);
			return (BUS_PROBE_DEFAULT);
		}
	}

	return (ENXIO);
}