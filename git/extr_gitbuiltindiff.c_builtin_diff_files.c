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
struct TYPE_2__ {int output_format; int /*<<< orphan*/  pathspec; } ;
struct rev_info {int max_count; int combine_merges; int dense_combined_merges; TYPE_1__ diffopt; } ;

/* Variables and functions */
 int DIFF_FORMAT_PATCH ; 
 unsigned int DIFF_SILENT_ON_REMOVED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  builtin_diff_usage ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ read_cache_preload (int /*<<< orphan*/ *) ; 
 int run_diff_files (struct rev_info*,unsigned int) ; 
 int /*<<< orphan*/  setup_work_tree () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int builtin_diff_files(struct rev_info *revs, int argc, const char **argv)
{
	unsigned int options = 0;

	while (1 < argc && argv[1][0] == '-') {
		if (!strcmp(argv[1], "--base"))
			revs->max_count = 1;
		else if (!strcmp(argv[1], "--ours"))
			revs->max_count = 2;
		else if (!strcmp(argv[1], "--theirs"))
			revs->max_count = 3;
		else if (!strcmp(argv[1], "-q"))
			options |= DIFF_SILENT_ON_REMOVED;
		else if (!strcmp(argv[1], "-h"))
			usage(builtin_diff_usage);
		else
			return error(_("invalid option: %s"), argv[1]);
		argv++; argc--;
	}

	/*
	 * "diff --base" should not combine merges because it was not
	 * asked to.  "diff -c" should not densify (if the user wants
	 * dense one, --cc can be explicitly asked for, or just rely
	 * on the default).
	 */
	if (revs->max_count == -1 && !revs->combine_merges &&
	    (revs->diffopt.output_format & DIFF_FORMAT_PATCH))
		revs->combine_merges = revs->dense_combined_merges = 1;

	setup_work_tree();
	if (read_cache_preload(&revs->diffopt.pathspec) < 0) {
		perror("read_cache_preload");
		return -1;
	}
	return run_diff_files(revs, options);
}