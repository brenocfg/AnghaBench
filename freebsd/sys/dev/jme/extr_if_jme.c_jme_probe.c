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
struct jme_dev {scalar_t__ jme_vendorid; scalar_t__ jme_deviceid; int /*<<< orphan*/  jme_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jme_dev* jme_devs ; 
 int nitems (struct jme_dev*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jme_probe(device_t dev)
{
	struct jme_dev *sp;
	int i;
	uint16_t vendor, devid;

	vendor = pci_get_vendor(dev);
	devid = pci_get_device(dev);
	sp = jme_devs;
	for (i = 0; i < nitems(jme_devs); i++, sp++) {
		if (vendor == sp->jme_vendorid &&
		    devid == sp->jme_deviceid) {
			device_set_desc(dev, sp->jme_name);
			return (BUS_PROBE_DEFAULT);
		}
	}

	return (ENXIO);
}