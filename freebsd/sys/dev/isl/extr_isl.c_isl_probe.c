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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_VENDOR ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int iicbus_get_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ init_device (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
isl_probe(device_t dev)
{
	uint32_t addr = iicbus_get_addr(dev);

	if (addr != 0x88)
		return (ENXIO);
	if (init_device(dev, 1) != 0)
		return (ENXIO);
	device_set_desc(dev, "ISL Digital Ambient Light Sensor");
	return (BUS_PROBE_VENDOR);
}