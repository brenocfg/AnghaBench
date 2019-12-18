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
 int AR9130_DEVID ; 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int VENDOR_ATHEROS ; 
 char* ath_hal_probe (int,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
ath_ahb_probe(device_t dev)
{
	int vendor_id, device_id;
	const char* devname;

	/*
	 * Check if a device/vendor ID is provided in hints.
	 */
	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "vendor_id", &vendor_id) != 0) {
		vendor_id = VENDOR_ATHEROS;
	}

	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "device_id", &device_id) != 0) {
		device_id = AR9130_DEVID;
	}

	device_printf(dev, "Vendor=0x%04x, Device=0x%04x\n",
	    vendor_id & 0xffff,
	    device_id & 0xffff);

	/* Attempt to probe */
	devname = ath_hal_probe(vendor_id, device_id);

	if (devname != NULL) {
		device_set_desc(dev, devname);
		return BUS_PROBE_DEFAULT;
	}
	return ENXIO;
}