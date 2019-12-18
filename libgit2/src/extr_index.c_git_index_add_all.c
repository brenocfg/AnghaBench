#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/  pathspec; } ;
typedef  TYPE_1__ git_pathspec ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index_matched_path_cb ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 unsigned int GIT_INDEX_ADD_CHECK_PATHSPEC ; 
 unsigned int GIT_INDEX_ADD_DISABLE_PATHSPEC_MATCH ; 
 unsigned int GIT_INDEX_ADD_FORCE ; 
 int /*<<< orphan*/  INDEX_ACTION_ADDALL ; 
 int /*<<< orphan*/ * INDEX_OWNER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set_after_callback (int) ; 
 int git_ignore__check_pathspec_for_exact_ignores (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec__clear (TYPE_1__*) ; 
 int git_pathspec__init (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 int index_apply_to_wd_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ,void*) ; 

int git_index_add_all(
	git_index *index,
	const git_strarray *paths,
	unsigned int flags,
	git_index_matched_path_cb cb,
	void *payload)
{
	int error;
	git_repository *repo;
	git_iterator *wditer = NULL;
	git_pathspec ps;
	bool no_fnmatch = (flags & GIT_INDEX_ADD_DISABLE_PATHSPEC_MATCH) != 0;

	assert(index);

	repo = INDEX_OWNER(index);
	if ((error = git_repository__ensure_not_bare(repo, "index add all")) < 0)
		return error;

	if ((error = git_pathspec__init(&ps, paths)) < 0)
		return error;

	/* optionally check that pathspec doesn't mention any ignored files */
	if ((flags & GIT_INDEX_ADD_CHECK_PATHSPEC) != 0 &&
		(flags & GIT_INDEX_ADD_FORCE) == 0 &&
		(error = git_ignore__check_pathspec_for_exact_ignores(
			repo, &ps.pathspec, no_fnmatch)) < 0)
		goto cleanup;

	error = index_apply_to_wd_diff(index, INDEX_ACTION_ADDALL, paths, flags, cb, payload);

	if (error)
		git_error_set_after_callback(error);

cleanup:
	git_iterator_free(wditer);
	git_pathspec__clear(&ps);

	return error;
}