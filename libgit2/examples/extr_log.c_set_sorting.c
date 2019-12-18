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
struct log_state {char* repodir; unsigned int sorting; int /*<<< orphan*/  walker; int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 unsigned int GIT_SORT_REVERSE ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_repository_open_ext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void set_sorting(struct log_state *s, unsigned int sort_mode)
{
	/** Open repo on demand if it isn't already open. */
	if (!s->repo) {
		if (!s->repodir) s->repodir = ".";
		check_lg2(git_repository_open_ext(&s->repo, s->repodir, 0, NULL),
			"Could not open repository", s->repodir);
	}

	/** Create revwalker on demand if it doesn't already exist. */
	if (!s->walker)
		check_lg2(git_revwalk_new(&s->walker, s->repo),
			"Could not create revision walker", NULL);

	if (sort_mode == GIT_SORT_REVERSE)
		s->sorting = s->sorting ^ GIT_SORT_REVERSE;
	else
		s->sorting = sort_mode | (s->sorting & GIT_SORT_REVERSE);

	git_revwalk_sorting(s->walker, s->sorting);
}