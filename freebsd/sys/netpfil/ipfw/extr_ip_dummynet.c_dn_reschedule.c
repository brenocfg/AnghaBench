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
 int C_DIRECT_EXEC ; 
 int C_HARDCLOCK ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ dn_gone ; 
 int /*<<< orphan*/  dn_timeout ; 
 int /*<<< orphan*/  dummynet ; 
 int /*<<< orphan*/  tick_sbt ; 

void
dn_reschedule(void)
{

	if (dn_gone != 0)
		return;
	callout_reset_sbt(&dn_timeout, tick_sbt, 0, dummynet, NULL,
	    C_HARDCLOCK | C_DIRECT_EXEC);
}