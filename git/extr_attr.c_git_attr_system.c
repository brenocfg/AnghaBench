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
 int /*<<< orphan*/  git_env_bool (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_attr_system(void)
{
	return !git_env_bool("GIT_ATTR_NOSYSTEM", 0);
}