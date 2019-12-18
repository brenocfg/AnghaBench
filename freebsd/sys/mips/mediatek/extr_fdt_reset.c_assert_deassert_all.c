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
 int FDT_RESET_ASSERT (int /*<<< orphan*/ *,int) ; 
 int FDT_RESET_DEASSERT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int) ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
assert_deassert_all(device_t consumer, boolean_t assert)
{
	phandle_t rnode;
	device_t resetdev;
	int resetnum, err, i, ncells;
	uint32_t *resets;
	boolean_t anyerrors;

	rnode = ofw_bus_get_node(consumer);
	ncells = OF_getencprop_alloc_multi(rnode, "resets", sizeof(*resets),
	    (void **)&resets);
	if (!assert && ncells < 2) {
		device_printf(consumer, "Warning: No resets specified in fdt "
		    "data; device may not function.");
		return (ENXIO);
	}
	anyerrors = false;
	for (i = 0; i < ncells; i += 2) {
		resetdev = OF_device_from_xref(resets[i]);
		resetnum = resets[i + 1];
		if (resetdev == NULL) {
			if (!assert)
				device_printf(consumer, "Warning: can not find "
				    "driver for reset number %u; device may "
				    "not function\n", resetnum);
			anyerrors = true;
			continue;
		}
		if (assert)
			err = FDT_RESET_ASSERT(resetdev, resetnum);
		else
			err = FDT_RESET_DEASSERT(resetdev, resetnum);
		if (err != 0) {
			if (!assert)
				device_printf(consumer, "Warning: failed to "
				    "deassert reset number %u; device may not "
				    "function\n", resetnum);
			anyerrors = true;
		}
	}
	OF_prop_free(resets);
	return (anyerrors ? ENXIO : 0);
}