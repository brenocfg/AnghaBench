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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int ENXIO ; 
 int FDT_CLOCK_DISABLE (int /*<<< orphan*/ *,int) ; 
 int FDT_CLOCK_ENABLE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int) ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
enable_disable_all(device_t consumer, boolean_t enable)
{
	phandle_t cnode;
	device_t clockdev;
	int clocknum, err, i, ncells;
	uint32_t *clks;
	boolean_t anyerrors;

	cnode = ofw_bus_get_node(consumer);
	ncells = OF_getencprop_alloc_multi(cnode, "clocks", sizeof(*clks),
	    (void **)&clks);
	if (enable && ncells < 2) {
		device_printf(consumer, "Warning: No clocks specified in fdt "
		    "data; device may not function.");
		return (ENXIO);
	}
	anyerrors = false;
	for (i = 0; i < ncells; i += 2) {
		clockdev = OF_device_from_xref(clks[i]);
		clocknum = clks[i + 1];
		if (clockdev == NULL) {
			if (enable)
				device_printf(consumer, "Warning: can not find "
				    "driver for clock number %u; device may not "
				    "function\n", clocknum);
			anyerrors = true;
			continue;
		}
		if (enable)
			err = FDT_CLOCK_ENABLE(clockdev, clocknum);
		else
			err = FDT_CLOCK_DISABLE(clockdev, clocknum);
		if (err != 0) {
			if (enable)
				device_printf(consumer, "Warning: failed to "
				    "enable clock number %u; device may not "
				    "function\n", clocknum);
			anyerrors = true;
		}
	}
	OF_prop_free(clks);
	return (anyerrors ? ENXIO : 0);
}