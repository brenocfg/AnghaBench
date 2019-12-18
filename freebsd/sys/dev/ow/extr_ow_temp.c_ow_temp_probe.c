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
#define  OWT_DS1820 131 
#define  OWT_DS1822 130 
#define  OWT_DS1825 129 
#define  OWT_DS18B20 128 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int ow_get_family (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ow_temp_probe(device_t dev)
{

	switch (ow_get_family(dev)) {
	case OWT_DS1820:
		device_set_desc(dev, "One Wire Temperature");
		return BUS_PROBE_DEFAULT;
	case OWT_DS1822:
	case OWT_DS1825:
	case OWT_DS18B20:
		device_set_desc(dev, "Advanced One Wire Temperature");
		return BUS_PROBE_DEFAULT;
	default:
		return ENXIO;
	}
}