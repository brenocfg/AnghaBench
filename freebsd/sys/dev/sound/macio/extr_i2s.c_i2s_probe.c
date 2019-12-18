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
typedef  int /*<<< orphan*/  subchildname ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_getprop (scalar_t__,char*,char*,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
i2s_probe(device_t self)
{
	const char 		*name;
	phandle_t		subchild;
	char			subchildname[255];

	name = ofw_bus_get_name(self);
	if (!name)
		return (ENXIO);

	if (strcmp(name, "i2s") != 0)
		return (ENXIO);

	/*
	 * Do not attach to "lightshow" I2S devices on Xserves. This controller
	 * is used there to control the LEDs on the front panel, and this
	 * driver can't handle it.
	 */
	subchild = OF_child(OF_child(ofw_bus_get_node(self)));
	if (subchild != 0 && OF_getprop(subchild, "name", subchildname,
	    sizeof(subchildname)) > 0 && strcmp(subchildname, "lightshow") == 0)
		return (ENXIO);
	
	device_set_desc(self, "Apple I2S Audio Controller");

	return (0);
}