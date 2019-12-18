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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int pinctrl_register_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int
fdt_pinctrl_register(device_t pinctrl, const char *pinprop)
{
	phandle_t node;
	int ret;

	TSENTER();
	node = ofw_bus_get_node(pinctrl);
	OF_device_register_xref(OF_xref_from_node(node), pinctrl);
	ret = pinctrl_register_children(pinctrl, node, pinprop);
	TSEXIT();

	return (ret);
}