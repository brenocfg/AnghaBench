#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_8__ {int state; } ;
struct TYPE_7__ {scalar_t__ enhsp0; } ;
typedef  TYPE_1__ Switch ;
typedef  TYPE_2__ Port ;
typedef  TYPE_3__ Node ;

/* Variables and functions */
 scalar_t__ IB_NODE_SWITCH ; 

__attribute__((used)) static int is_port_inactive(Node * node, Port * port, Switch * sw)
{
	int res = 0;
	if (port->state != 4 &&
	    (node->type != IB_NODE_SWITCH ||
	     (node->type == IB_NODE_SWITCH && sw->enhsp0)))
		res = 1;
	return res;
}