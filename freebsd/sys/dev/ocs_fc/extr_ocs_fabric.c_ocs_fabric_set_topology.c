#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_sport_topology_e ;
struct TYPE_5__ {TYPE_1__* sport; } ;
typedef  TYPE_2__ ocs_node_t ;
struct TYPE_4__ {int /*<<< orphan*/  topology; } ;

/* Variables and functions */

void
ocs_fabric_set_topology(ocs_node_t *node, ocs_sport_topology_e topology)
{
	node->sport->topology = topology;
}