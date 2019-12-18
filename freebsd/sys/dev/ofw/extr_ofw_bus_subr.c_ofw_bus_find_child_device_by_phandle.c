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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int OFW_BUS_GET_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

device_t
ofw_bus_find_child_device_by_phandle(device_t bus, phandle_t node)
{
	device_t *children, retval, child;
	int nkid, i;

	/*
	 * Nothing can match the flag value for no node.
	 */
	if (node == -1)
		return (NULL);

	/*
	 * Search the children for a match. We microoptimize
	 * a bit by not using ofw_bus_get since we already know
	 * the parent. We do not recurse.
	 */
	if (device_get_children(bus, &children, &nkid) != 0)
		return (NULL);
	retval = NULL;
	for (i = 0; i < nkid; i++) {
		child = children[i];
		if (OFW_BUS_GET_NODE(bus, child) == node) {
			retval = child;
			break;
		}
	}
	free(children, M_TEMP);

	return (retval);
}