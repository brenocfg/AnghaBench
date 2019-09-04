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
 int /*<<< orphan*/  get_git_dir () ; 
 scalar_t__ inside_git_dir ; 
 scalar_t__ is_inside_dir (int /*<<< orphan*/ ) ; 

int is_inside_git_dir(void)
{
	if (inside_git_dir < 0)
		inside_git_dir = is_inside_dir(get_git_dir());
	return inside_git_dir;
}