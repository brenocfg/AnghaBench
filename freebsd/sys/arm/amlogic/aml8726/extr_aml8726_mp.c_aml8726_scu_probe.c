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
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* scu_compatible ; 

__attribute__((used)) static int
aml8726_scu_probe(device_t dev)
{
	int i;

	for (i = 0; scu_compatible[i]; i++)
		if (ofw_bus_is_compatible(dev, scu_compatible[i]))
			break;

	if (!scu_compatible[i])
		return (ENXIO);

	device_set_desc(dev, "ARM Snoop Control Unit");

	return (BUS_PROBE_DEFAULT);
}