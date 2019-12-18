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
typedef  int /*<<< orphan*/  ibnd_fabric_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NODE_CA ; 
 int /*<<< orphan*/  IB_NODE_ROUTER ; 
 int /*<<< orphan*/  IB_NODE_SWITCH ; 
 int LIST_CA_NODE ; 
 int LIST_ROUTER_NODE ; 
 int LIST_SWITCH_NODE ; 
 int /*<<< orphan*/  ibnd_iter_nodes_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_node ; 

void list_nodes(ibnd_fabric_t * fabric, int list)
{
	if (list & LIST_CA_NODE)
		ibnd_iter_nodes_type(fabric, list_node, IB_NODE_CA, NULL);
	if (list & LIST_SWITCH_NODE)
		ibnd_iter_nodes_type(fabric, list_node, IB_NODE_SWITCH, NULL);
	if (list & LIST_ROUTER_NODE)
		ibnd_iter_nodes_type(fabric, list_node, IB_NODE_ROUTER, NULL);
}