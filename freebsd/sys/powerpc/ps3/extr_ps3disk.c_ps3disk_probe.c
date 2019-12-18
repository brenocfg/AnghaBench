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
 int BUS_PROBE_SPECIFIC ; 
 int ENXIO ; 
 scalar_t__ PS3_BUSTYPE_STORAGE ; 
 scalar_t__ PS3_DEVTYPE_DISK ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ps3bus_get_bustype (int /*<<< orphan*/ ) ; 
 scalar_t__ ps3bus_get_devtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ps3disk_probe(device_t dev)
{
	if (ps3bus_get_bustype(dev) != PS3_BUSTYPE_STORAGE ||
	    ps3bus_get_devtype(dev) != PS3_DEVTYPE_DISK)
		return (ENXIO);

	device_set_desc(dev, "Playstation 3 Disk");

	return (BUS_PROBE_SPECIFIC);
}