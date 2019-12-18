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
struct software_node {scalar_t__ name; } ;

/* Variables and functions */
 int software_node_register (struct software_node const*) ; 
 int /*<<< orphan*/  software_node_unregister_nodes (struct software_node const*) ; 

int software_node_register_nodes(const struct software_node *nodes)
{
	int ret;
	int i;

	for (i = 0; nodes[i].name; i++) {
		ret = software_node_register(&nodes[i]);
		if (ret) {
			software_node_unregister_nodes(nodes);
			return ret;
		}
	}

	return 0;
}