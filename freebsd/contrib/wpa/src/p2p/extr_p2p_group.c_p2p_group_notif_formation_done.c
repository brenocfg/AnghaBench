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
struct p2p_group {int beacon_update; scalar_t__ group_formation; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_group_update_ies (struct p2p_group*) ; 

void p2p_group_notif_formation_done(struct p2p_group *group)
{
	if (group == NULL)
		return;
	group->group_formation = 0;
	group->beacon_update = 1;
	p2p_group_update_ies(group);
}