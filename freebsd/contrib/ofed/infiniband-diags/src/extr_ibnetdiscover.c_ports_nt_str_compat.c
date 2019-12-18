#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ ibnd_node_t ;

/* Variables and functions */
#define  IB_NODE_CA 130 
#define  IB_NODE_ROUTER 129 
#define  IB_NODE_SWITCH 128 

__attribute__((used)) static inline const char *ports_nt_str_compat(ibnd_node_t * node)
{
	switch (node->type) {
	case IB_NODE_SWITCH:
		return "SW";
	case IB_NODE_CA:
		return "CA";
	case IB_NODE_ROUTER:
		return "RT";
	}
	return "??";
}