#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next_chassis_node; TYPE_2__* chassis; } ;
typedef  TYPE_1__ ibnd_node_t ;
struct TYPE_6__ {TYPE_1__* nodes; } ;
typedef  TYPE_2__ ibnd_chassis_t ;

/* Variables and functions */

__attribute__((used)) static void add_node_to_chassis(ibnd_chassis_t * chassis, ibnd_node_t * node)
{
	node->chassis = chassis;
	node->next_chassis_node = chassis->nodes;
	chassis->nodes = node;
}