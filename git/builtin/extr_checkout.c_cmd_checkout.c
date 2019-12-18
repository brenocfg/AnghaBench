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
struct checkout_opts {int new_branch_log; int dwim_new_local_branch; int overlay_mode; int switch_branch_doing_nothing_is_ok; int only_merge_on_switching_branches; int accept_ref; int accept_pathspec; int implicit_detach; int can_switch_when_in_progress; int empty_pathspec_ok; int checkout_index; int checkout_worktree; scalar_t__ orphan_from_empty_tree; int /*<<< orphan*/  new_branch_force; int /*<<< orphan*/  new_branch; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (struct option*) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (char,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (char,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option* add_checkout_path_options (struct checkout_opts*,struct option*) ; 
 struct option* add_common_options (struct checkout_opts*,struct option*) ; 
 struct option* add_common_switch_branch_options (struct checkout_opts*,struct option*) ; 
 int checkout_main (int,char const**,char const*,struct checkout_opts*,struct option*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkout_usage ; 
 int /*<<< orphan*/  memset (struct checkout_opts*,int /*<<< orphan*/ ,int) ; 
 struct option* parse_options_dup (struct option*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int cmd_checkout(int argc, const char **argv, const char *prefix)
{
	struct checkout_opts opts;
	struct option *options;
	struct option checkout_options[] = {
		OPT_STRING('b', NULL, &opts.new_branch, N_("branch"),
			   N_("create and checkout a new branch")),
		OPT_STRING('B', NULL, &opts.new_branch_force, N_("branch"),
			   N_("create/reset and checkout a branch")),
		OPT_BOOL('l', NULL, &opts.new_branch_log, N_("create reflog for new branch")),
		OPT_BOOL(0, "guess", &opts.dwim_new_local_branch,
			 N_("second guess 'git checkout <no-such-branch>' (default)")),
		OPT_BOOL(0, "overlay", &opts.overlay_mode, N_("use overlay mode (default)")),
		OPT_END()
	};
	int ret;

	memset(&opts, 0, sizeof(opts));
	opts.dwim_new_local_branch = 1;
	opts.switch_branch_doing_nothing_is_ok = 1;
	opts.only_merge_on_switching_branches = 0;
	opts.accept_ref = 1;
	opts.accept_pathspec = 1;
	opts.implicit_detach = 1;
	opts.can_switch_when_in_progress = 1;
	opts.orphan_from_empty_tree = 0;
	opts.empty_pathspec_ok = 1;
	opts.overlay_mode = -1;
	opts.checkout_index = -2;    /* default on */
	opts.checkout_worktree = -2; /* default on */

	if (argc == 3 && !strcmp(argv[1], "-b")) {
		/*
		 * User ran 'git checkout -b <branch>' and expects
		 * the same behavior as 'git switch -c <branch>'.
		 */
		opts.switch_branch_doing_nothing_is_ok = 0;
		opts.only_merge_on_switching_branches = 1;
	}

	options = parse_options_dup(checkout_options);
	options = add_common_options(&opts, options);
	options = add_common_switch_branch_options(&opts, options);
	options = add_checkout_path_options(&opts, options);

	ret = checkout_main(argc, argv, prefix, &opts,
			    options, checkout_usage);
	FREE_AND_NULL(options);
	return ret;
}