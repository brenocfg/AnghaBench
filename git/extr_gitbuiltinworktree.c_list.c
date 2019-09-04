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
struct worktree {int dummy; } ;
struct option {int dummy; } ;

/* Variables and functions */
 int DEFAULT_ABBREV ; 
 int /*<<< orphan*/  GWT_SORT_LINKED ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  measure_widths (struct worktree**,int*,int*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_worktree (struct worktree*,int,int) ; 
 int /*<<< orphan*/  show_worktree_porcelain (struct worktree*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 int /*<<< orphan*/  worktree_usage ; 

__attribute__((used)) static int list(int ac, const char **av, const char *prefix)
{
	int porcelain = 0;

	struct option options[] = {
		OPT_BOOL(0, "porcelain", &porcelain, N_("machine-readable output")),
		OPT_END()
	};

	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (ac)
		usage_with_options(worktree_usage, options);
	else {
		struct worktree **worktrees = get_worktrees(GWT_SORT_LINKED);
		int path_maxlen = 0, abbrev = DEFAULT_ABBREV, i;

		if (!porcelain)
			measure_widths(worktrees, &abbrev, &path_maxlen);

		for (i = 0; worktrees[i]; i++) {
			if (porcelain)
				show_worktree_porcelain(worktrees[i]);
			else
				show_worktree(worktrees[i], path_maxlen, abbrev);
		}
		free_worktrees(worktrees);
	}
	return 0;
}