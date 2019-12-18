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
struct ofw_compat_data {scalar_t__ ocd_data; int /*<<< orphan*/ * ocd_str; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 struct ofw_compat_data* compat_data ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bcm2835_cpufreq_identify(driver_t *driver, device_t parent)
{
	const struct ofw_compat_data *compat;
	phandle_t root;

	root = OF_finddevice("/");
	for (compat = compat_data; compat->ocd_str != NULL; compat++)
		if (ofw_bus_node_is_compatible(root, compat->ocd_str))
			break;

	if (compat->ocd_data == 0)
		return;

	DPRINTF("driver=%p, parent=%p\n", driver, parent);
	if (device_find_child(parent, "bcm2835_cpufreq", -1) != NULL)
		return;
	if (BUS_ADD_CHILD(parent, 0, "bcm2835_cpufreq", -1) == NULL)
		device_printf(parent, "add child failed\n");
}