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
 scalar_t__ SCHEDULER_STOPPED () ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  i40e_msec_delay (int) ; 
 int /*<<< orphan*/  ixl_ms_scale (int) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 

void
i40e_msec_pause(int msecs)
{
	if (cold || SCHEDULER_STOPPED())
		i40e_msec_delay(msecs);
	else
		// ERJ: (msecs * hz) could overflow
		pause("ixl", ixl_ms_scale(msecs));
}