#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ length; scalar_t__ contents; } ;
typedef  TYPE_3__ git_vector ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_11__ {scalar_t__ count; char** strings; } ;
struct TYPE_14__ {int /*<<< orphan*/  ignore_submodules; TYPE_1__ pathspec; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ git_diff_options ;
struct TYPE_12__ {size_t length; } ;
struct TYPE_15__ {TYPE_2__ deltas; } ;
typedef  TYPE_5__ git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_DISABLE_PATHSPEC_MATCH ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_4__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_ALL ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (TYPE_5__*) ; 
 int git_diff_index_to_workdir (TYPE_5__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static int merge_check_workdir(size_t *conflicts, git_repository *repo, git_index *index_new, git_vector *merged_paths)
{
	git_diff *wd_diff_list = NULL;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	int error = 0;

	GIT_UNUSED(index_new);

	*conflicts = 0;

	/* We need to have merged at least 1 file for the possibility to exist to
	 * have conflicts with the workdir. Passing 0 as the pathspec count paramter
	 * will consider all files in the working directory, that is, we may detect
	 * a conflict if there were untracked files in the workdir prior to starting
	 * the merge. This typically happens when cherry-picking a commmit whose
	 * changes have already been applied.
	 */
	if (merged_paths->length == 0)
		return 0;

	opts.flags |= GIT_DIFF_INCLUDE_UNTRACKED;

	/* Workdir changes may exist iff they do not conflict with changes that
	 * will be applied by the merge (including conflicts).  Ensure that there
	 * are no changes in the workdir to these paths.
	 */
	opts.flags |= GIT_DIFF_DISABLE_PATHSPEC_MATCH;
	opts.pathspec.count = merged_paths->length;
	opts.pathspec.strings = (char **)merged_paths->contents;
	opts.ignore_submodules = GIT_SUBMODULE_IGNORE_ALL;

	if ((error = git_diff_index_to_workdir(&wd_diff_list, repo, NULL, &opts)) < 0)
		goto done;

	*conflicts = wd_diff_list->deltas.length;

done:
	git_diff_free(wd_diff_list);

	return error;
}