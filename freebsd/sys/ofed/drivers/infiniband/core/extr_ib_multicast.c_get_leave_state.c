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
typedef  int u8 ;
struct TYPE_2__ {int join_state; } ;
struct mcast_group {TYPE_1__ rec; int /*<<< orphan*/ * members; } ;

/* Variables and functions */
 int NUM_JOIN_MEMBERSHIP_TYPES ; 

__attribute__((used)) static u8 get_leave_state(struct mcast_group *group)
{
	u8 leave_state = 0;
	int i;

	for (i = 0; i < NUM_JOIN_MEMBERSHIP_TYPES; i++)
		if (!group->members[i])
			leave_state |= (0x1 << i);

	return leave_state & group->rec.join_state;
}