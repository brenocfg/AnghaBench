#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  phandle_t ;
struct TYPE_2__ {int mask; int /*<<< orphan*/ * compat; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_PM_CTRL ; 
 int dev_mask ; 
 TYPE_1__* fdt_pm_mask_table ; 
 int ofw_bus_node_is_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_cpu_ctrl (int /*<<< orphan*/ ) ; 

int
mv_fdt_pm(phandle_t node)
{
	uint32_t cpu_pm_ctrl;
	int i, ena, compat;

	ena = 1;
	cpu_pm_ctrl = read_cpu_ctrl(CPU_PM_CTRL);
	for (i = 0; fdt_pm_mask_table[i].compat != NULL; i++) {
		if (dev_mask & (1 << i))
			continue;

		compat = ofw_bus_node_is_compatible(node,
		    fdt_pm_mask_table[i].compat);
#if defined(SOC_MV_KIRKWOOD)
		if (compat && (cpu_pm_ctrl & fdt_pm_mask_table[i].mask)) {
			dev_mask |= (1 << i);
			ena = 0;
			break;
		} else if (compat) {
			dev_mask |= (1 << i);
			break;
		}
#else
		if (compat && (~cpu_pm_ctrl & fdt_pm_mask_table[i].mask)) {
			dev_mask |= (1 << i);
			ena = 0;
			break;
		} else if (compat) {
			dev_mask |= (1 << i);
			break;
		}
#endif
	}

	return (ena);
}