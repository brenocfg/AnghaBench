#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pathspec_match_context {int dummy; } ;
struct TYPE_15__ {size_t length; } ;
typedef  TYPE_1__ git_vector ;
struct TYPE_16__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  failures; int /*<<< orphan*/  matches; } ;
typedef  TYPE_2__ git_pathspec_match_list ;
struct TYPE_17__ {int /*<<< orphan*/  prefix; TYPE_1__ pathspec; } ;
typedef  TYPE_3__ git_pathspec ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_18__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_4__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_bitvec ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_ANY ; 
 scalar_t__ GIT_ITERATOR_TYPE_WORKDIR ; 
 int GIT_ITEROVER ; 
 int GIT_PATHSPEC_FAILURES_ONLY ; 
 int GIT_PATHSPEC_FIND_FAILURES ; 
 int GIT_PATHSPEC_NO_GLOB ; 
 int GIT_PATHSPEC_NO_MATCH_ERROR ; 
 int /*<<< orphan*/  PATHSPEC_DATATYPE_STRINGS ; 
 scalar_t__ git_array_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_bitvec_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_bitvec_init (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_index__find_pos (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_iterator_advance (TYPE_4__ const**,int /*<<< orphan*/ *) ; 
 scalar_t__ git_iterator_current_is_ignored (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_ignore_case (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_owner (int /*<<< orphan*/ *) ; 
 int git_iterator_reset_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_iterator_type (int /*<<< orphan*/ *) ; 
 int git_pathspec__match_at (size_t*,TYPE_1__*,struct pathspec_match_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* git_pool_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int pathspec_build_failure_array (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pathspec_mark_pattern (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ pathspec_mark_remaining (int /*<<< orphan*/ *,TYPE_1__*,struct pathspec_match_context*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* pathspec_match_alloc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathspec_match_context_init (struct pathspec_match_context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathspec_match_free (TYPE_2__*) ; 

__attribute__((used)) static int pathspec_match_from_iterator(
	git_pathspec_match_list **out,
	git_iterator *iter,
	uint32_t flags,
	git_pathspec *ps)
{
	int error = 0;
	git_pathspec_match_list *m = NULL;
	const git_index_entry *entry = NULL;
	struct pathspec_match_context ctxt;
	git_vector *patterns = &ps->pathspec;
	bool find_failures = out && (flags & GIT_PATHSPEC_FIND_FAILURES) != 0;
	bool failures_only = !out || (flags & GIT_PATHSPEC_FAILURES_ONLY) != 0;
	size_t pos, used_ct = 0, found_files = 0;
	git_index *index = NULL;
	git_bitvec used_patterns;
	char **file;

	if (git_bitvec_init(&used_patterns, patterns->length) < 0)
		return -1;

	if (out) {
		*out = m = pathspec_match_alloc(ps, PATHSPEC_DATATYPE_STRINGS);
		GIT_ERROR_CHECK_ALLOC(m);
	}

	if ((error = git_iterator_reset_range(iter, ps->prefix, ps->prefix)) < 0)
		goto done;

	if (git_iterator_type(iter) == GIT_ITERATOR_TYPE_WORKDIR &&
		(error = git_repository_index__weakptr(
			&index, git_iterator_owner(iter))) < 0)
		goto done;

	pathspec_match_context_init(
		&ctxt, (flags & GIT_PATHSPEC_NO_GLOB) != 0,
		git_iterator_ignore_case(iter));

	while (!(error = git_iterator_advance(&entry, iter))) {
		/* search for match with entry->path */
		int result = git_pathspec__match_at(
			&pos, patterns, &ctxt, entry->path, NULL);

		/* no matches for this path */
		if (result < 0)
			continue;

		/* if result was a negative pattern match, then don't list file */
		if (!result) {
			used_ct += pathspec_mark_pattern(&used_patterns, pos);
			continue;
		}

		/* check if path is ignored and untracked */
		if (index != NULL &&
			git_iterator_current_is_ignored(iter) &&
			git_index__find_pos(NULL, index, entry->path, 0, GIT_INDEX_STAGE_ANY) < 0)
			continue;

		/* mark the matched pattern as used */
		used_ct += pathspec_mark_pattern(&used_patterns, pos);
		++found_files;

		/* if find_failures is on, check if any later patterns also match */
		if (find_failures && used_ct < patterns->length)
			used_ct += pathspec_mark_remaining(
				&used_patterns, patterns, &ctxt, pos + 1, entry->path, NULL);

		/* if only looking at failures, exit early or just continue */
		if (failures_only || !out) {
			if (used_ct == patterns->length)
				break;
			continue;
		}

		/* insert matched path into matches array */
		if ((file = (char **)git_array_alloc(m->matches)) == NULL ||
			(*file = git_pool_strdup(&m->pool, entry->path)) == NULL) {
			error = -1;
			goto done;
		}
	}

	if (error < 0 && error != GIT_ITEROVER)
		goto done;
	error = 0;

	/* insert patterns that had no matches into failures array */
	if (find_failures && used_ct < patterns->length &&
		(error = pathspec_build_failure_array(
			&m->failures, patterns, &used_patterns, &m->pool)) < 0)
		goto done;

	/* if every pattern failed to match, then we have failed */
	if ((flags & GIT_PATHSPEC_NO_MATCH_ERROR) != 0 && !found_files) {
		git_error_set(GIT_ERROR_INVALID, "no matching files were found");
		error = GIT_ENOTFOUND;
	}

done:
	git_bitvec_free(&used_patterns);

	if (error < 0) {
		pathspec_match_free(m);
		if (out) *out = NULL;
	}

	return error;
}