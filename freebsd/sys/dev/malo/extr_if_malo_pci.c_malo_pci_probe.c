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
struct malo_product {scalar_t__ mp_vendorid; scalar_t__ mp_deviceid; int /*<<< orphan*/  mp_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct malo_product* malo_products ; 
 int nitems (struct malo_product*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
malo_pci_probe(device_t dev)
{
	struct malo_product *mp;
	uint16_t vendor, devid;
	int i;

	vendor = pci_get_vendor(dev);
	devid = pci_get_device(dev);
	mp = malo_products;

	for (i = 0; i < nitems(malo_products); i++, mp++) {
		if (vendor == mp->mp_vendorid && devid == mp->mp_deviceid) {
			device_set_desc(dev, mp->mp_name);
			return (BUS_PROBE_DEFAULT);
		}
	}

	return (ENXIO);
}