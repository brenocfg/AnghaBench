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
 scalar_t__ TT_MODE_OFF ; 
 unsigned long long UM_NSEC_PER_SEC ; 
 int /*<<< orphan*/  os_idle_sleep (unsigned long long) ; 
 scalar_t__ time_travel_mode ; 
 int /*<<< orphan*/  time_travel_sleep (unsigned long long) ; 

__attribute__((used)) static void um_idle_sleep(void)
{
	unsigned long long duration = UM_NSEC_PER_SEC;

	if (time_travel_mode != TT_MODE_OFF) {
		time_travel_sleep(duration);
	} else {
		os_idle_sleep(duration);
	}
}