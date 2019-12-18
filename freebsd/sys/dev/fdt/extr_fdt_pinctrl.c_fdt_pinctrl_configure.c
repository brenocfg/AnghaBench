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
typedef  int u_int ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FDT_PINCTRL_CONFIGURE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_prop_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int
fdt_pinctrl_configure(device_t client, u_int index)
{
	device_t pinctrl;
	phandle_t *configs;
	int i, nconfigs;
	char name[16];

	snprintf(name, sizeof(name), "pinctrl-%u", index);
	nconfigs = OF_getencprop_alloc_multi(ofw_bus_get_node(client), name,
	    sizeof(*configs), (void **)&configs);
	if (nconfigs < 0)
		return (ENOENT);
	if (nconfigs == 0)
		return (0); /* Empty property is documented as valid. */
	for (i = 0; i < nconfigs; i++) {
		if ((pinctrl = OF_device_from_xref(configs[i])) != NULL)
			FDT_PINCTRL_CONFIGURE(pinctrl, configs[i]);
	}
	OF_prop_free(configs);
	return (0);
}