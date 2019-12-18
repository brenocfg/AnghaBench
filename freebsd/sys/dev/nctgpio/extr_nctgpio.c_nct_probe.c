#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {scalar_t__ chip_id; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ NCT_LDN_GPIO ; 
 scalar_t__ SUPERIO_DEV_GPIO ; 
 scalar_t__ SUPERIO_VENDOR_NUVOTON ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* nct_devs ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ superio_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ superio_get_ldn (int /*<<< orphan*/ ) ; 
 scalar_t__ superio_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ superio_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nct_probe(device_t dev)
{
	int j;
	uint16_t chipid;

	if (superio_vendor(dev) != SUPERIO_VENDOR_NUVOTON)
		return (ENXIO);
	if (superio_get_type(dev) != SUPERIO_DEV_GPIO)
		return (ENXIO);

	/*
	 * There are several GPIO devices, we attach only to one of them
	 * and use the rest without attaching.
	 */
	if (superio_get_ldn(dev) != NCT_LDN_GPIO)
		return (ENXIO);

	chipid = superio_devid(dev);
	for (j = 0; j < nitems(nct_devs); j++) {
		if (chipid == nct_devs[j].chip_id) {
			device_set_desc(dev, "Nuvoton GPIO controller");
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}