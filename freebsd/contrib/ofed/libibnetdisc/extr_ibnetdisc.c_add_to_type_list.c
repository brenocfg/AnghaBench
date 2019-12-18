#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; struct TYPE_6__* type_next; } ;
typedef  TYPE_1__ ibnd_node_t ;
struct TYPE_7__ {TYPE_1__* routers; TYPE_1__* switches; TYPE_1__* ch_adapters; } ;
typedef  TYPE_2__ ibnd_fabric_t ;
struct TYPE_8__ {TYPE_2__ fabric; } ;
typedef  TYPE_3__ f_internal_t ;

/* Variables and functions */
#define  IB_NODE_CA 130 
#define  IB_NODE_ROUTER 129 
#define  IB_NODE_SWITCH 128 

void add_to_type_list(ibnd_node_t * node, f_internal_t * f_int)
{
	ibnd_fabric_t *fabric = &f_int->fabric;
	switch (node->type) {
	case IB_NODE_CA:
		node->type_next = fabric->ch_adapters;
		fabric->ch_adapters = node;
		break;
	case IB_NODE_SWITCH:
		node->type_next = fabric->switches;
		fabric->switches = node;
		break;
	case IB_NODE_ROUTER:
		node->type_next = fabric->routers;
		fabric->routers = node;
		break;
	}
}