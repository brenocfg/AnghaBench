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
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 scalar_t__ OF_getprop_alloc (scalar_t__,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int USB_EN ; 
 int UTMI_PHY_EN ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_usb(device_t dev, bus_space_tag_t iot, bus_space_handle_t ioh)
{
	int tmp;
	phandle_t node;
	char *phy_type;

	phy_type = NULL;
	tmp = bus_space_read_4(iot, ioh, CONTROL) | USB_EN;

	node = ofw_bus_get_node(dev);
	if ((node != 0) &&
	    (OF_getprop_alloc(node, "phy_type", (void **)&phy_type) > 0)) {
		if (strncasecmp(phy_type, "utmi", strlen("utmi")) == 0)
			tmp |= UTMI_PHY_EN;
		OF_prop_free(phy_type);
	}
	bus_space_write_4(iot, ioh, CONTROL, tmp);
}