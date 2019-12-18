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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cpufreq_dt_identify(driver_t *driver, device_t parent)
{
	phandle_t node;

	/* Properties must be listed under node /cpus/cpu@0 */
	node = ofw_bus_get_node(parent);

	/* The cpu@0 node must have the following properties */
	if (!OF_hasprop(node, "clocks") ||
	    (!OF_hasprop(node, "cpu-supply") &&
	    !OF_hasprop(node, "cpu0-supply")))
		return;

	if (!OF_hasprop(node, "operating-points") &&
	    !OF_hasprop(node, "operating-points-v2"))
		return;

	if (device_find_child(parent, "cpufreq_dt", -1) != NULL)
		return;

	if (BUS_ADD_CHILD(parent, 0, "cpufreq_dt", -1) == NULL)
		device_printf(parent, "add cpufreq_dt child failed\n");
}