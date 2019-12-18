#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stash_info {int /*<<< orphan*/  w_commit; int /*<<< orphan*/  b_commit; } ;
struct TYPE_6__ {int recursive; } ;
struct TYPE_7__ {TYPE_1__ flags; int /*<<< orphan*/  output_format; } ;
struct rev_info {TYPE_2__ diffopt; } ;
struct option {int dummy; } ;
struct argv_array {int argc; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  DIFF_FORMAT_DIFFSTAT ; 
 int /*<<< orphan*/  DIFF_FORMAT_PATCH ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int diff_result_code (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_setup_done (TYPE_2__*) ; 
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  free_stash_info (struct stash_info*) ; 
 int get_stash_info (struct stash_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_ui_config ; 
 int /*<<< orphan*/  git_stash_config ; 
 int /*<<< orphan*/  git_stash_show_usage ; 
 int /*<<< orphan*/  init_diff_ui_defaults () ; 
 int /*<<< orphan*/  init_revisions (struct rev_info*,char const*) ; 
 int /*<<< orphan*/  log_tree_diff_flush (struct rev_info*) ; 
 int /*<<< orphan*/  setup_diff_pager (TYPE_2__*) ; 
 int setup_revisions (int,int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ show_patch ; 
 scalar_t__ show_stat ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

__attribute__((used)) static int show_stash(int argc, const char **argv, const char *prefix)
{
	int i;
	int ret = 0;
	struct stash_info info;
	struct rev_info rev;
	struct argv_array stash_args = ARGV_ARRAY_INIT;
	struct argv_array revision_args = ARGV_ARRAY_INIT;
	struct option options[] = {
		OPT_END()
	};

	init_diff_ui_defaults();
	git_config(git_diff_ui_config, NULL);
	init_revisions(&rev, prefix);

	argv_array_push(&revision_args, argv[0]);
	for (i = 1; i < argc; i++) {
		if (argv[i][0] != '-')
			argv_array_push(&stash_args, argv[i]);
		else
			argv_array_push(&revision_args, argv[i]);
	}

	ret = get_stash_info(&info, stash_args.argc, stash_args.argv);
	argv_array_clear(&stash_args);
	if (ret)
		return -1;

	/*
	 * The config settings are applied only if there are not passed
	 * any options.
	 */
	if (revision_args.argc == 1) {
		git_config(git_stash_config, NULL);
		if (show_stat)
			rev.diffopt.output_format = DIFF_FORMAT_DIFFSTAT;

		if (show_patch)
			rev.diffopt.output_format |= DIFF_FORMAT_PATCH;

		if (!show_stat && !show_patch) {
			free_stash_info(&info);
			return 0;
		}
	}

	argc = setup_revisions(revision_args.argc, revision_args.argv, &rev, NULL);
	if (argc > 1) {
		free_stash_info(&info);
		usage_with_options(git_stash_show_usage, options);
	}
	if (!rev.diffopt.output_format) {
		rev.diffopt.output_format = DIFF_FORMAT_PATCH;
		diff_setup_done(&rev.diffopt);
	}

	rev.diffopt.flags.recursive = 1;
	setup_diff_pager(&rev.diffopt);
	diff_tree_oid(&info.b_commit, &info.w_commit, "", &rev.diffopt);
	log_tree_diff_flush(&rev);

	free_stash_info(&info);
	return diff_result_code(&rev.diffopt, 0);
}