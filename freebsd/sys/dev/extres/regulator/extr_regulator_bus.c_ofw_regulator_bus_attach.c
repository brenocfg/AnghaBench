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
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplebus_add_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ofw_regulator_bus_attach(device_t dev)
{
	phandle_t node, child;

	node  = ofw_bus_get_node(dev);
	simplebus_init(dev, node);

	for (child = OF_child(node); child > 0; child = OF_peer(child)) {
		simplebus_add_device(dev, child, 0, NULL, -1, NULL);
	}

	return (bus_generic_attach(dev));
}