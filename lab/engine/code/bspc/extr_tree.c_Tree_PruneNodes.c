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
typedef  int /*<<< orphan*/  node_t ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  Tree_PruneNodes_r (int /*<<< orphan*/ *) ; 
 scalar_t__ c_pruned ; 

void Tree_PruneNodes(node_t *node)
{
	Log_Print("------- Prune Nodes --------\n");
	c_pruned = 0;
	Tree_PruneNodes_r(node);
	Log_Print("%5i pruned nodes\n", c_pruned);
}