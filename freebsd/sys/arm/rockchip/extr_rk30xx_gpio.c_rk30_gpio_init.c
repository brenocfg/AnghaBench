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
struct gpio_ctrl_entry {int (* handler ) (scalar_t__,int /*<<< orphan*/ *,int) ;scalar_t__ compat; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  gpios ;

/* Variables and functions */
 int ENXIO ; 
 int GPIOS_PROP_CELLS ; 
 int MAX_PINS_PER_NODE ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getencprop (scalar_t__,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (scalar_t__,char*) ; 
 scalar_t__ OF_node_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  gpio_controllers ; 
 scalar_t__ ofw_bus_node_is_compatible (scalar_t__,scalar_t__) ; 
 int stub1 (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
rk30_gpio_init(void)
{
	phandle_t child, parent, root, ctrl;
	pcell_t gpios[MAX_PINS_PER_NODE * GPIOS_PROP_CELLS];
	struct gpio_ctrl_entry *e;
	int len, rv;

	root = OF_finddevice("/");
	len = 0;
	parent = root;

	/* Traverse through entire tree to find nodes with 'gpios' prop */
	for (child = OF_child(parent); child != 0; child = OF_peer(child)) {

		/* Find a 'leaf'. Start the search from this node. */
		while (OF_child(child)) {
			parent = child;
			child = OF_child(child);
		}
		if ((len = OF_getproplen(child, "gpios")) > 0) {

			if (len > sizeof(gpios))
				return (ENXIO);

			/* Get 'gpios' property. */
			OF_getencprop(child, "gpios", gpios, len);

			e = (struct gpio_ctrl_entry *)&gpio_controllers;

			/* Find and call a handler. */
			for (; e->compat; e++) {
				/*
				 * First cell of 'gpios' property should
				 * contain a ref. to a node defining GPIO
				 * controller.
				 */
				ctrl = OF_node_from_xref(gpios[0]);

				if (ofw_bus_node_is_compatible(ctrl, e->compat))
					/* Call a handler. */
					if ((rv = e->handler(ctrl,
					    (pcell_t *)&gpios, len)))
						return (rv);
			}
		}

		if (OF_peer(child) == 0) {
			/* No more siblings. */
			child = parent;
			parent = OF_parent(child);
		}
	}
	return (0);
}