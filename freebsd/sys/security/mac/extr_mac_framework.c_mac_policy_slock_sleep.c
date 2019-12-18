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
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mac_late ; 
 int /*<<< orphan*/  mac_policy_sx ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 

void
mac_policy_slock_sleep(void)
{

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
 	    "mac_policy_slock_sleep");

#ifndef MAC_STATIC
	if (!mac_late)
		return;

	sx_slock(&mac_policy_sx);
#endif
}