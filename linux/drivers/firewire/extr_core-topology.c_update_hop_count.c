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
struct fw_node {int port_count; int max_depth; int /*<<< orphan*/  max_hops; TYPE_1__** ports; } ;
struct TYPE_2__ {int max_hops; int max_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int,int) ; 

__attribute__((used)) static void update_hop_count(struct fw_node *node)
{
	int depths[2] = { -1, -1 };
	int max_child_hops = 0;
	int i;

	for (i = 0; i < node->port_count; i++) {
		if (node->ports[i] == NULL)
			continue;

		if (node->ports[i]->max_hops > max_child_hops)
			max_child_hops = node->ports[i]->max_hops;

		if (node->ports[i]->max_depth > depths[0]) {
			depths[1] = depths[0];
			depths[0] = node->ports[i]->max_depth;
		} else if (node->ports[i]->max_depth > depths[1])
			depths[1] = node->ports[i]->max_depth;
	}

	node->max_depth = depths[0] + 1;
	node->max_hops = max(max_child_hops, depths[0] + depths[1] + 2);
}