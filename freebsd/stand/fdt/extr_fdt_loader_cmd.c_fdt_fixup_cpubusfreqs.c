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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int FDT_ERR_NOTFOUND ; 
 int MIN (int,int) ; 
 int fdt_next_node (int /*<<< orphan*/ ,int,int*) ; 
 int fdt_node_offset_by_prop_value (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/  const*,int) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_setprop_inplace_cell (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtp ; 

void
fdt_fixup_cpubusfreqs(unsigned long cpufreq, unsigned long busfreq)
{
	int lo, o = 0, o2, maxo = 0, depth;
	const uint32_t zero = 0;

	/* We want to modify every subnode of /cpus */
	o = fdt_path_offset(fdtp, "/cpus");
	if (o < 0)
		return;

	/* maxo should contain offset of node next to /cpus */
	depth = 0;
	maxo = o;
	while (depth != -1)
		maxo = fdt_next_node(fdtp, maxo, &depth);

	/* Find CPU frequency properties */
	o = fdt_node_offset_by_prop_value(fdtp, o, "clock-frequency",
	    &zero, sizeof(uint32_t));

	o2 = fdt_node_offset_by_prop_value(fdtp, o, "bus-frequency", &zero,
	    sizeof(uint32_t));

	lo = MIN(o, o2);

	while (o != -FDT_ERR_NOTFOUND && o2 != -FDT_ERR_NOTFOUND) {

		o = fdt_node_offset_by_prop_value(fdtp, lo,
		    "clock-frequency", &zero, sizeof(uint32_t));

		o2 = fdt_node_offset_by_prop_value(fdtp, lo, "bus-frequency",
		    &zero, sizeof(uint32_t));

		/* We're only interested in /cpus subnode(s) */
		if (lo > maxo)
			break;

		fdt_setprop_inplace_cell(fdtp, lo, "clock-frequency",
		    (uint32_t)cpufreq);

		fdt_setprop_inplace_cell(fdtp, lo, "bus-frequency",
		    (uint32_t)busfreq);

		lo = MIN(o, o2);
	}
}