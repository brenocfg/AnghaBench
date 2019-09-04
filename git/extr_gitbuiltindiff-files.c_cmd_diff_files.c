#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int output_format; int /*<<< orphan*/  pathspec; } ;
struct TYPE_3__ {scalar_t__ nr; } ;
struct rev_info {int max_count; int min_age; int max_age; int combine_merges; int dense_combined_merges; TYPE_2__ diffopt; TYPE_1__ pending; scalar_t__ abbrev; } ;

/* Variables and functions */
 int DIFF_FORMAT_PATCH ; 
 int DIFF_FORMAT_RAW ; 
 unsigned int DIFF_SILENT_ON_REMOVED ; 
 int /*<<< orphan*/  diff_files_usage ; 
 int diff_result_code (TYPE_2__*,int) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_basic_config ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  precompose_argv (int,char const**) ; 
 scalar_t__ read_cache_preload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,char const*) ; 
 int run_diff_files (struct rev_info*,unsigned int) ; 
 int setup_revisions (int,char const**,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int cmd_diff_files(int argc, const char **argv, const char *prefix)
{
	struct rev_info rev;
	int result;
	unsigned options = 0;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(diff_files_usage);

	git_config(git_diff_basic_config, NULL); /* no "diff" UI options */
	repo_init_revisions(the_repository, &rev, prefix);
	rev.abbrev = 0;
	precompose_argv(argc, argv);

	argc = setup_revisions(argc, argv, &rev, NULL);
	while (1 < argc && argv[1][0] == '-') {
		if (!strcmp(argv[1], "--base"))
			rev.max_count = 1;
		else if (!strcmp(argv[1], "--ours"))
			rev.max_count = 2;
		else if (!strcmp(argv[1], "--theirs"))
			rev.max_count = 3;
		else if (!strcmp(argv[1], "-q"))
			options |= DIFF_SILENT_ON_REMOVED;
		else
			usage(diff_files_usage);
		argv++; argc--;
	}
	if (!rev.diffopt.output_format)
		rev.diffopt.output_format = DIFF_FORMAT_RAW;

	/*
	 * Make sure there are NO revision (i.e. pending object) parameter,
	 * rev.max_count is reasonable (0 <= n <= 3), and
	 * there is no other revision filtering parameters.
	 */
	if (rev.pending.nr ||
	    rev.min_age != -1 || rev.max_age != -1 ||
	    3 < rev.max_count)
		usage(diff_files_usage);

	/*
	 * "diff-files --base -p" should not combine merges because it
	 * was not asked to.  "diff-files -c -p" should not densify
	 * (the user should ask with "diff-files --cc" explicitly).
	 */
	if (rev.max_count == -1 && !rev.combine_merges &&
	    (rev.diffopt.output_format & DIFF_FORMAT_PATCH))
		rev.combine_merges = rev.dense_combined_merges = 1;

	if (read_cache_preload(&rev.diffopt.pathspec) < 0) {
		perror("read_cache_preload");
		return -1;
	}
	result = run_diff_files(&rev, options);
	return diff_result_code(&rev.diffopt, result);
}