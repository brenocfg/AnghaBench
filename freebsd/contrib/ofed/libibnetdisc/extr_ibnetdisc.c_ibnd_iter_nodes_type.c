#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* type_next; } ;
typedef  TYPE_1__ ibnd_node_t ;
typedef  int /*<<< orphan*/  (* ibnd_iter_node_func_t ) (TYPE_1__*,void*) ;
struct TYPE_7__ {TYPE_1__* routers; TYPE_1__* ch_adapters; TYPE_1__* switches; } ;
typedef  TYPE_3__ ibnd_fabric_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_DEBUG (char*,...) ; 
#define  IB_NODE_CA 130 
#define  IB_NODE_ROUTER 129 
#define  IB_NODE_SWITCH 128 

void ibnd_iter_nodes_type(ibnd_fabric_t * fabric, ibnd_iter_node_func_t func,
			  int node_type, void *user_data)
{
	ibnd_node_t *list = NULL;
	ibnd_node_t *cur = NULL;

	if (!fabric) {
		IBND_DEBUG("fabric parameter NULL\n");
		return;
	}

	if (!func) {
		IBND_DEBUG("func parameter NULL\n");
		return;
	}

	switch (node_type) {
	case IB_NODE_SWITCH:
		list = fabric->switches;
		break;
	case IB_NODE_CA:
		list = fabric->ch_adapters;
		break;
	case IB_NODE_ROUTER:
		list = fabric->routers;
		break;
	default:
		IBND_DEBUG("Invalid node_type specified %d\n", node_type);
		break;
	}

	for (cur = list; cur; cur = cur->type_next)
		func(cur, user_data);
}