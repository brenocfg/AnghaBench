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
 int git_env_bool (char*,int /*<<< orphan*/ ) ; 

int use_gettext_poison(void)
{
	static int poison_requested = -1;
	if (poison_requested == -1)
		poison_requested = git_env_bool("GIT_TEST_GETTEXT_POISON", 0);
	return poison_requested;
}