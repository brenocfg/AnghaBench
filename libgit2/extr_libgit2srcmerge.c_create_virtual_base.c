#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_16__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_merge_options ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_17__ {int /*<<< orphan*/  parents; int /*<<< orphan*/ * index; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ANNOTATED_COMMIT_VIRTUAL ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_MERGE_FAIL_ON_CONFLICT ; 
 TYPE_1__ GIT_MERGE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_MERGE__VIRTUAL_BASE ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  insert_head_ids (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 scalar_t__ merge_annotated_commits (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,size_t,TYPE_1__*) ; 

__attribute__((used)) static int create_virtual_base(
	git_annotated_commit **out,
	git_repository *repo,
	git_annotated_commit *one,
	git_annotated_commit *two,
	const git_merge_options *opts,
	size_t recursion_level)
{
	git_annotated_commit *result = NULL;
	git_index *index = NULL;
	git_merge_options virtual_opts = GIT_MERGE_OPTIONS_INIT;

	/* Conflicts in the merge base creation do not propagate to conflicts
	 * in the result; the conflicted base will act as the common ancestor.
	 */
	if (opts)
		memcpy(&virtual_opts, opts, sizeof(git_merge_options));

	virtual_opts.flags &= ~GIT_MERGE_FAIL_ON_CONFLICT;
	virtual_opts.flags |= GIT_MERGE__VIRTUAL_BASE;

	if ((merge_annotated_commits(&index, NULL, repo, one, two,
			recursion_level + 1, &virtual_opts)) < 0)
		return -1;

	result = git__calloc(1, sizeof(git_annotated_commit));
	GIT_ERROR_CHECK_ALLOC(result);
	result->type = GIT_ANNOTATED_COMMIT_VIRTUAL;
	result->index = index;

	insert_head_ids(&result->parents, one);
	insert_head_ids(&result->parents, two);

	*out = result;
	return 0;
}