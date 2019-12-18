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
typedef  scalar_t__ uint32_t ;
struct intsmb_device {scalar_t__ devid; int /*<<< orphan*/  description; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intsmb_device* intsmb_products ; 
 size_t nitems (struct intsmb_device*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intsmb_probe(device_t dev)
{
	const struct intsmb_device *isd;
	uint32_t devid;
	size_t i;

	devid = pci_get_devid(dev);
	for (i = 0; i < nitems(intsmb_products); i++) {
		isd = &intsmb_products[i];
		if (isd->devid == devid) {
			device_set_desc(dev, isd->description);
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}