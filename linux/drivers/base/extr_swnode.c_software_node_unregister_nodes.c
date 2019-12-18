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
struct swnode {int /*<<< orphan*/  fwnode; } ;
struct software_node {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwnode_remove_software_node (int /*<<< orphan*/ *) ; 
 struct swnode* software_node_to_swnode (struct software_node const*) ; 

void software_node_unregister_nodes(const struct software_node *nodes)
{
	struct swnode *swnode;
	int i;

	for (i = 0; nodes[i].name; i++) {
		swnode = software_node_to_swnode(&nodes[i]);
		if (swnode)
			fwnode_remove_software_node(&swnode->fwnode);
	}
}