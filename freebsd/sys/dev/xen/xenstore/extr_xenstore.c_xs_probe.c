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
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int 
xs_probe(device_t dev)
{
	/*
	 * We are either operating within a PV kernel or being probed
	 * as the child of the successfully attached xenpci device.
	 * Thus we are in a Xen environment and there will be a XenStore.
	 * Unconditionally return success.
	 */
	device_set_desc(dev, "XenStore");
	return (BUS_PROBE_NOWILDCARD);
}