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
struct device_node {int dummy; } ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_node_to_nid_single (struct device_node*) ; 

int of_node_to_nid(struct device_node *device)
{
	int nid = NUMA_NO_NODE;

	of_node_get(device);
	while (device) {
		nid = of_node_to_nid_single(device);
		if (nid != -1)
			break;

		device = of_get_next_parent(device);
	}
	of_node_put(device);

	return nid;
}