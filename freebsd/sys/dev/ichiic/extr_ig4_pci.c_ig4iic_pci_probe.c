#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ ig4iic_softc_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {scalar_t__ devid; int /*<<< orphan*/  version; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ig4iic_pci_devices ; 
 int nitems (TYPE_2__*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ig4iic_pci_probe(device_t dev)
{
	ig4iic_softc_t *sc = device_get_softc(dev);
	uint32_t devid;
	int i;

	devid = pci_get_devid(dev);
	for (i = 0; i < nitems(ig4iic_pci_devices); i++) {
		if (ig4iic_pci_devices[i].devid == devid) {
			device_set_desc(dev, ig4iic_pci_devices[i].desc);
			sc->version = ig4iic_pci_devices[i].version;
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}