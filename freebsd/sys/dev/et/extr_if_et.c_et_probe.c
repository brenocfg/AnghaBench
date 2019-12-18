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
struct et_dev {scalar_t__ vid; scalar_t__ did; int /*<<< orphan*/ * desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct et_dev* et_devices ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
et_probe(device_t dev)
{
	const struct et_dev *d;
	uint16_t did, vid;

	vid = pci_get_vendor(dev);
	did = pci_get_device(dev);

	for (d = et_devices; d->desc != NULL; ++d) {
		if (vid == d->vid && did == d->did) {
			device_set_desc(dev, d->desc);
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}