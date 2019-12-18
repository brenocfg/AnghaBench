#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ocd_str; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  compats ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpc85xx_cache_probe(device_t dev)
{

	if (ofw_bus_search_compatible(dev, compats)->ocd_str == NULL)
		return (ENXIO);

	device_set_desc(dev, "MPC85xx L2 cache");
	return (0);
}