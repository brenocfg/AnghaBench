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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 char* reparent_relative_path (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_git_dir_1 (char*) ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  trace_setup_key ; 

__attribute__((used)) static void update_relative_gitdir(const char *name,
				   const char *old_cwd,
				   const char *new_cwd,
				   void *data)
{
	char *path = reparent_relative_path(old_cwd, new_cwd, get_git_dir());
	trace_printf_key(&trace_setup_key,
			 "setup: move $GIT_DIR to '%s'",
			 path);
	set_git_dir_1(path);
	free(path);
}