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
struct fdt_clock_info {int index; char* name; int /*<<< orphan*/ * provider; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int FDT_CLOCK_GET_INFO (int /*<<< orphan*/ *,int,struct fdt_clock_info*) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int) ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  bzero (struct fdt_clock_info*,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 

int
fdt_clock_get_info(device_t consumer, int n, struct fdt_clock_info *info)
{
	phandle_t cnode;
	device_t clockdev;
	int clocknum, err, ncells;
	uint32_t *clks;

	cnode = ofw_bus_get_node(consumer);
	ncells = OF_getencprop_alloc_multi(cnode, "clocks", sizeof(*clks),
	    (void **)&clks);
	if (ncells <= 0)
		return (ENXIO);
	n *= 2;
	if (ncells <= n)
		err = ENXIO;
	else {
		clockdev = OF_device_from_xref(clks[n]);
		if (clockdev == NULL)
			err = ENXIO;
		else  {
			/*
			 * Make struct contents minimally valid, then call
			 * provider to fill in what it knows (provider can
			 * override anything it wants to).
			 */
			clocknum = clks[n + 1];
			bzero(info, sizeof(*info));
			info->provider = clockdev;
			info->index = clocknum;
			info->name = "";
			err = FDT_CLOCK_GET_INFO(clockdev, clocknum, info);
		}
	}
	OF_prop_free(clks);
	return (err);
}