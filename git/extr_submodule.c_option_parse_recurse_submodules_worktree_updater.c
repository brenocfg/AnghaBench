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
struct option {int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECURSE_SUBMODULES_OFF ; 
 int /*<<< orphan*/  RECURSE_SUBMODULES_ON ; 
 int /*<<< orphan*/  config_update_recurse_submodules ; 
 int /*<<< orphan*/  parse_update_recurse_submodules_arg (int /*<<< orphan*/ ,char const*) ; 

int option_parse_recurse_submodules_worktree_updater(const struct option *opt,
						     const char *arg, int unset)
{
	if (unset) {
		config_update_recurse_submodules = RECURSE_SUBMODULES_OFF;
		return 0;
	}
	if (arg)
		config_update_recurse_submodules =
			parse_update_recurse_submodules_arg(opt->long_name,
							    arg);
	else
		config_update_recurse_submodules = RECURSE_SUBMODULES_ON;

	return 0;
}