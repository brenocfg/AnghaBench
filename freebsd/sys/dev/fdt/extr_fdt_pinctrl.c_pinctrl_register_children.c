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
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_hasprop (scalar_t__,char const*) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 

__attribute__((used)) static int
pinctrl_register_children(device_t pinctrl, phandle_t parent,
    const char *pinprop)
{
	phandle_t node;

	/*
	 * Recursively descend from parent, looking for nodes that have the
	 * given property, and associate the pinctrl device_t with each one.
	 */
	for (node = OF_child(parent); node != 0; node = OF_peer(node)) {
		pinctrl_register_children(pinctrl, node, pinprop);
		if (pinprop == NULL || OF_hasprop(node, pinprop)) {
			OF_device_register_xref(OF_xref_from_node(node),
			    pinctrl);
		}
	}
	return (0);
}