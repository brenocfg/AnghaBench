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
 int BUS_PROBE_VENDOR ; 
 int iflib_device_probe (int /*<<< orphan*/ ) ; 

int
iflib_device_probe_vendor(device_t dev)
{
	int probe;

	probe = iflib_device_probe(dev);
	if (probe == BUS_PROBE_DEFAULT)
		return (BUS_PROBE_VENDOR);
	else
		return (probe);
}