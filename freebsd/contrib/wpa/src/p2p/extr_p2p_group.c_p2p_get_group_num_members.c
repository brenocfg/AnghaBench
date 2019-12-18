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
struct p2p_group {unsigned int num_members; } ;

/* Variables and functions */

unsigned int p2p_get_group_num_members(struct p2p_group *group)
{
	if (!group)
		return 0;

	return group->num_members;
}