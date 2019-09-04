#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ignore_submodules; int ignore_untracked_in_submodules; int ignore_dirty_submodules; } ;
struct diff_options {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void handle_ignore_submodules_arg(struct diff_options *diffopt,
				  const char *arg)
{
	diffopt->flags.ignore_submodules = 0;
	diffopt->flags.ignore_untracked_in_submodules = 0;
	diffopt->flags.ignore_dirty_submodules = 0;

	if (!strcmp(arg, "all"))
		diffopt->flags.ignore_submodules = 1;
	else if (!strcmp(arg, "untracked"))
		diffopt->flags.ignore_untracked_in_submodules = 1;
	else if (!strcmp(arg, "dirty"))
		diffopt->flags.ignore_dirty_submodules = 1;
	else if (strcmp(arg, "none"))
		die("bad --ignore-submodules argument: %s", arg);
	/*
	 * Please update _git_status() in git-completion.bash when you
	 * add new options
	 */
}