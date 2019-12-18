#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_EBAREREPO ; 
 int GIT_ITERATOR_HONOR_IGNORES ; 
 int GIT_ITERATOR_IGNORE_DOT_GIT ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ITERATOR_TYPE_WORKDIR ; 
 scalar_t__ git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 
 int iterator_for_filesystem (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

int git_iterator_for_workdir_ext(
	git_iterator **out,
	git_repository *repo,
	const char *repo_workdir,
	git_index *index,
	git_tree *tree,
	git_iterator_options *given_opts)
{
	git_iterator_options options = GIT_ITERATOR_OPTIONS_INIT;

	if (!repo_workdir) {
		if (git_repository__ensure_not_bare(repo, "scan working directory") < 0)
			return GIT_EBAREREPO;

		repo_workdir = git_repository_workdir(repo);
	}

	/* upgrade to a workdir iterator, adding necessary internal flags */
	if (given_opts)
		memcpy(&options, given_opts, sizeof(git_iterator_options));

	options.flags |= GIT_ITERATOR_HONOR_IGNORES |
		GIT_ITERATOR_IGNORE_DOT_GIT;

	return iterator_for_filesystem(out,
		repo, repo_workdir, index, tree, GIT_ITERATOR_TYPE_WORKDIR, &options);
}