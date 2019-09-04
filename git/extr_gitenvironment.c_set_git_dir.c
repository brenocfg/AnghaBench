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
 int /*<<< orphan*/  chdir_notify_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_absolute_path (char const*) ; 
 int /*<<< orphan*/  set_git_dir_1 (char const*) ; 
 int /*<<< orphan*/  update_relative_gitdir ; 

void set_git_dir(const char *path)
{
	set_git_dir_1(path);
	if (!is_absolute_path(path))
		chdir_notify_register(NULL, update_relative_gitdir, NULL);
}