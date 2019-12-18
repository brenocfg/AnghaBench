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
 int /*<<< orphan*/  get_git_work_tree () ; 
 scalar_t__ is_bare_repository_cfg ; 

int is_bare_repository(void)
{
	/* if core.bare is not 'false', let's see if there is a work tree */
	return is_bare_repository_cfg && !get_git_work_tree();
}