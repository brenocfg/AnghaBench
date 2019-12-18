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
 scalar_t__ is_git_command (char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 char const* xstrfmt (char*,char const*) ; 

__attribute__((used)) static const char *cmd_to_page(const char *git_cmd)
{
	if (!git_cmd)
		return "git";
	else if (starts_with(git_cmd, "git"))
		return git_cmd;
	else if (is_git_command(git_cmd))
		return xstrfmt("git-%s", git_cmd);
	else
		return xstrfmt("git%s", git_cmd);
}