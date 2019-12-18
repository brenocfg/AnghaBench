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
struct p2p_group {scalar_t__ num_members; TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ max_clients; } ;

/* Variables and functions */

int p2p_client_limit_reached(struct p2p_group *group)
{
	if (!group || !group->cfg)
		return 1;

	return group->num_members >= group->cfg->max_clients;
}