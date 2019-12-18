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
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
creator_bus_probe(device_t dev)
{
	const char *name;
	phandle_t node;
	int type;

	name = ofw_bus_get_name(dev);
	node = ofw_bus_get_node(dev);
	if (strcmp(name, "SUNW,ffb") == 0) {
		if (OF_getprop(node, "board_type", &type, sizeof(type)) == -1)
			return (ENXIO);
		switch (type & 7) {
		case 0x0:
			device_set_desc(dev, "Creator");
			break;
		case 0x3:
			device_set_desc(dev, "Creator3D");
			break;
		default:
			return (ENXIO);
		}
	} else if (strcmp(name, "SUNW,afb") == 0)
		device_set_desc(dev, "Elite3D");
	else
		return (ENXIO);
	return (BUS_PROBE_DEFAULT);
}