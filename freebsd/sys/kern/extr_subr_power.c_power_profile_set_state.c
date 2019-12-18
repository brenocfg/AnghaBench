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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int POWER_PROFILE_PERFORMANCE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  power_profile_change ; 
 int power_profile_state ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
power_profile_set_state(int state) 
{
	int		changed;
    
	if (state != power_profile_state) {
		power_profile_state = state;
		changed = 1;
		if (bootverbose) {
			printf("system power profile changed to '%s'\n",
				(state == POWER_PROFILE_PERFORMANCE) ?
				"performance" : "economy");
		}
	} else {
		changed = 0;
	}

	if (changed)
		EVENTHANDLER_INVOKE(power_profile_change, 0);
}