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
struct option {int dummy; } ;
struct checkout_opts {int dwim_new_local_branch; int discard_changes; int accept_ref; int only_merge_on_switching_branches; int orphan_from_empty_tree; int overlay_mode; scalar_t__ can_switch_when_in_progress; scalar_t__ implicit_detach; scalar_t__ switch_branch_doing_nothing_is_ok; scalar_t__ accept_pathspec; int /*<<< orphan*/  new_branch_force; int /*<<< orphan*/  new_branch; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (struct option*) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (char,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option* add_common_options (struct checkout_opts*,struct option*) ; 
 struct option* add_common_switch_branch_options (struct checkout_opts*,struct option*) ; 
 int checkout_main (int,char const**,char const*,struct checkout_opts*,struct option*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct checkout_opts*,int /*<<< orphan*/ ,int) ; 
 struct option* parse_options_dup (struct option*) ; 
 int /*<<< orphan*/  switch_branch_usage ; 

int cmd_switch(int argc, const char **argv, const char *prefix)
{
	struct checkout_opts opts;
	struct option *options = NULL;
	struct option switch_options[] = {
		OPT_STRING('c', "create", &opts.new_branch, N_("branch"),
			   N_("create and switch to a new branch")),
		OPT_STRING('C', "force-create", &opts.new_branch_force, N_("branch"),
			   N_("create/reset and switch to a branch")),
		OPT_BOOL(0, "guess", &opts.dwim_new_local_branch,
			 N_("second guess 'git switch <no-such-branch>'")),
		OPT_BOOL(0, "discard-changes", &opts.discard_changes,
			 N_("throw away local modifications")),
		OPT_END()
	};
	int ret;

	memset(&opts, 0, sizeof(opts));
	opts.dwim_new_local_branch = 1;
	opts.accept_ref = 1;
	opts.accept_pathspec = 0;
	opts.switch_branch_doing_nothing_is_ok = 0;
	opts.only_merge_on_switching_branches = 1;
	opts.implicit_detach = 0;
	opts.can_switch_when_in_progress = 0;
	opts.orphan_from_empty_tree = 1;
	opts.overlay_mode = -1;

	options = parse_options_dup(switch_options);
	options = add_common_options(&opts, options);
	options = add_common_switch_branch_options(&opts, options);

	ret = checkout_main(argc, argv, prefix, &opts,
			    options, switch_branch_usage);
	FREE_AND_NULL(options);
	return ret;
}