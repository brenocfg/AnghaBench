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
typedef  int /*<<< orphan*/  VCHIQ_STATE_T ;
struct TYPE_3__ {scalar_t__ resume_blocked; int /*<<< orphan*/  videocore_use_count; scalar_t__ blocked_count; } ;
typedef  TYPE_1__ VCHIQ_ARM_STATE_T ;

/* Variables and functions */
 TYPE_1__* vchiq_platform_get_arm_state (int /*<<< orphan*/ *) ; 
 int vchiq_platform_videocore_wanted (int /*<<< orphan*/ *) ; 

int
vchiq_videocore_wanted(VCHIQ_STATE_T *state)
{
	VCHIQ_ARM_STATE_T *arm_state = vchiq_platform_get_arm_state(state);
	if (!arm_state)
		/* autosuspend not supported - always return wanted */
		return 1;
	else if (arm_state->blocked_count)
		return 1;
	else if (!arm_state->videocore_use_count)
		/* usage count zero - check for override unless we're forcing */
		if (arm_state->resume_blocked)
			return 0;
		else
			return vchiq_platform_videocore_wanted(state);
	else
		/* non-zero usage count - videocore still required */
		return 1;
}