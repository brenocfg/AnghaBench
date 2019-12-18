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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int fdt_pinctrl_configure (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char*) ; 

int
fdt_pinctrl_configure_by_name(device_t client, const char * name)
{
	char * names;
	int i, offset, nameslen;

	nameslen = OF_getprop_alloc(ofw_bus_get_node(client), "pinctrl-names",
	    (void **)&names);
	if (nameslen <= 0)
		return (ENOENT);
	for (i = 0, offset = 0; offset < nameslen; i++) {
		if (strcmp(name, &names[offset]) == 0)
			break;
		offset += strlen(&names[offset]) + 1;
	}
	OF_prop_free(names);
	if (offset < nameslen)
		return (fdt_pinctrl_configure(client, i));
	else
		return (ENOENT);
}