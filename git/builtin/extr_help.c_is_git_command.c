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
 scalar_t__ is_builtin (char const*) ; 
 scalar_t__ is_in_cmdlist (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  load_command_list (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_cmds ; 
 int /*<<< orphan*/  other_cmds ; 

__attribute__((used)) static int is_git_command(const char *s)
{
	if (is_builtin(s))
		return 1;

	load_command_list("git-", &main_cmds, &other_cmds);
	return is_in_cmdlist(&main_cmds, s) ||
		is_in_cmdlist(&other_cmds, s);
}