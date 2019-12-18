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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ SUPERIO_DEV_WDT ; 
 scalar_t__ SUPERIO_VENDOR_ITE ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ superio_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ superio_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
itwd_probe(device_t dev)
{

	if (superio_vendor(dev) != SUPERIO_VENDOR_ITE)
		return (ENXIO);
	if (superio_get_type(dev) != SUPERIO_DEV_WDT)
		return (ENXIO);
	device_set_desc(dev, "Watchdog Timer on ITE SuperIO");
	return (BUS_PROBE_DEFAULT);
}