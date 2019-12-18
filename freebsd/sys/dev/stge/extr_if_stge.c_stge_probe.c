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
struct stge_product {scalar_t__ stge_vendorid; scalar_t__ stge_deviceid; int /*<<< orphan*/  stge_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nitems (struct stge_product*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 struct stge_product* stge_products ; 

__attribute__((used)) static int
stge_probe(device_t dev)
{
	const struct stge_product *sp;
	int i;
	uint16_t vendor, devid;

	vendor = pci_get_vendor(dev);
	devid = pci_get_device(dev);
	sp = stge_products;
	for (i = 0; i < nitems(stge_products); i++, sp++) {
		if (vendor == sp->stge_vendorid &&
		    devid == sp->stge_deviceid) {
			device_set_desc(dev, sp->stge_name);
			return (BUS_PROBE_DEFAULT);
		}
	}

	return (ENXIO);
}