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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  model ;
typedef  int /*<<< orphan*/  gp ;
typedef  int /*<<< orphan*/  device_t ;
typedef  char cell_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  OF_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
rbled_probe(device_t dev)
{
	phandle_t node;
	const char *name;
	cell_t gp[2];
	char model[6];

	node = ofw_bus_get_node(dev);

	name = ofw_bus_get_name(dev);
	if (name == NULL)
		return (ENXIO);
	if (strcmp(name, "led") != 0)
		return (ENXIO);

	if (OF_getprop(node, "user_led", gp, sizeof(gp)) <= 0)
		return (ENXIO);

	/* Check root model. */
	node = OF_peer(0);
	if (OF_getprop(node, "model", model, sizeof(model)) <= 0)
		return (ENXIO);
	if (strcmp(model, "RB800") != 0)
		return (ENXIO);

	device_set_desc(dev, "RouterBoard LED");
	return (0);
}