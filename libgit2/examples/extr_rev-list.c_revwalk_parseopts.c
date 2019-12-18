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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 unsigned int GIT_SORT_NONE ; 
 unsigned int GIT_SORT_REVERSE ; 
 unsigned int GIT_SORT_TIME ; 
 unsigned int GIT_SORT_TOPOLOGICAL ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ *,unsigned int) ; 
 int push_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int push_spec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int revwalk_parseopts(git_repository *repo, git_revwalk *walk, int nopts, char **opts)
{
	int hide, i, error;
	unsigned int sorting = GIT_SORT_NONE;

	hide = 0;
	for (i = 0; i < nopts; i++) {
		if (!strcmp(opts[i], "--topo-order")) {
			sorting = GIT_SORT_TOPOLOGICAL | (sorting & GIT_SORT_REVERSE);
			git_revwalk_sorting(walk, sorting);
		} else if (!strcmp(opts[i], "--date-order")) {
			sorting = GIT_SORT_TIME | (sorting & GIT_SORT_REVERSE);
			git_revwalk_sorting(walk, sorting);
		} else if (!strcmp(opts[i], "--reverse")) {
			sorting = (sorting & ~GIT_SORT_REVERSE)
			    | ((sorting & GIT_SORT_REVERSE) ? 0 : GIT_SORT_REVERSE);
			git_revwalk_sorting(walk, sorting);
		} else if (!strcmp(opts[i], "--not")) {
			hide = !hide;
		} else if (opts[i][0] == '^') {
			if ((error = push_spec(repo, walk, opts[i] + 1, !hide)))
				return error;
		} else if (strstr(opts[i], "..")) {
			if ((error = push_range(repo, walk, opts[i], hide)))
				return error;
		} else {
			if ((error = push_spec(repo, walk, opts[i], hide)))
				return error;
		}
	}

	return 0;
}