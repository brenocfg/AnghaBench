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
struct age_dev {scalar_t__ age_vendorid; scalar_t__ age_deviceid; int /*<<< orphan*/  age_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 struct age_dev* age_devs ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nitems (struct age_dev*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
age_probe(device_t dev)
{
	struct age_dev *sp;
	int i;
	uint16_t vendor, devid;

	vendor = pci_get_vendor(dev);
	devid = pci_get_device(dev);
	sp = age_devs;
	for (i = 0; i < nitems(age_devs); i++, sp++) {
		if (vendor == sp->age_vendorid &&
		    devid == sp->age_deviceid) {
			device_set_desc(dev, sp->age_name);
			return (BUS_PROBE_DEFAULT);
		}
	}

	return (ENXIO);
}