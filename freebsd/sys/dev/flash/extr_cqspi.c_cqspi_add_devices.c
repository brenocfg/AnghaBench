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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/ * simplebus_add_device (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cqspi_add_devices(device_t dev)
{
	phandle_t child, node;
	device_t child_dev;
	int error;

	node = ofw_bus_get_node(dev);

	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		child_dev =
		    simplebus_add_device(dev, child, 0, NULL, -1, NULL);
		if (child_dev == NULL) {
			return (ENXIO);
		}

		error = device_probe_and_attach(child_dev);
		if (error != 0) {
			printf("can't probe and attach: %d\n", error);
		}
	}

	return (0);
}