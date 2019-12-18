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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  min_freq ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmufreq_identify(driver_t *driver, device_t parent)
{
	phandle_t node;
	uint32_t min_freq;

	node = ofw_bus_get_node(parent);
	if (OF_getprop(node, "min-clock-frequency", &min_freq, sizeof(min_freq)) == -1)
		return;

	/* Make sure we're not being doubly invoked. */
	if (device_find_child(parent, "pmufreq", -1) != NULL)
		return;

	/*
	 * We attach a child for every CPU since settings need to
	 * be performed on every CPU in the SMP case.
	 */
	if (BUS_ADD_CHILD(parent, 10, "pmufreq", -1) == NULL)
		device_printf(parent, "add pmufreq child failed\n");
}