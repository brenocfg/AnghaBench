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
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 int /*<<< orphan*/ * device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
nvdimm_e820_probe(device_t dev)
{
	/*
	 * nexus panics if a child doesn't have ivars.  BUS_ADD_CHILD uses
	 * nexus_add_child, which creates fuckin ivars.  but sometimes if you
	 * unload and reload nvdimm_e820, the device node stays but the ivars
	 * are deleted??? avoid trivial panic but this is a kludge.
	 */
	if (device_get_ivars(dev) == NULL)
		return (ENXIO);

	device_quiet(dev);
	device_set_desc(dev, "Legacy e820 NVDIMM root device");
	return (BUS_PROBE_NOWILDCARD);
}