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
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
src_probe(device_t dev)
{

        if ((ofw_bus_is_compatible(dev, "fsl,imx6q-src") == 0) &&
            (ofw_bus_is_compatible(dev, "fsl,imx6-src") == 0))
		return (ENXIO);

	device_set_desc(dev, "Freescale i.MX6 System Reset Controller");

	return (BUS_PROBE_DEFAULT);
}