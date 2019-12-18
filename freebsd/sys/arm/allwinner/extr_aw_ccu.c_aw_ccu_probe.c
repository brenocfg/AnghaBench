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
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int BUS_PROBE_SPECIFIC ; 
 int ENXIO ; 
 TYPE_1__* aw_ccu_search_compatible () ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
aw_ccu_probe(device_t dev)
{
	const char *name;

	name = ofw_bus_get_name(dev);

	if (name == NULL || strcmp(name, "clocks") != 0)
		return (ENXIO);

	if (aw_ccu_search_compatible()->ocd_data == 0)
		return (ENXIO);

	device_set_desc(dev, "Allwinner Clock Control Unit");
	return (BUS_PROBE_SPECIFIC);
}