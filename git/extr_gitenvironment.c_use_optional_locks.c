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
 int /*<<< orphan*/  GIT_OPTIONAL_LOCKS_ENVIRONMENT ; 
 int git_env_bool (int /*<<< orphan*/ ,int) ; 

int use_optional_locks(void)
{
	return git_env_bool(GIT_OPTIONAL_LOCKS_ENVIRONMENT, 1);
}