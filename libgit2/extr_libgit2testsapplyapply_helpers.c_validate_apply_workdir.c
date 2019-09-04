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
struct merge_index_entry {int dummy; } ;
struct iterator_compare_data {size_t member_1; int /*<<< orphan*/  cnt; int /*<<< orphan*/  idx; struct merge_index_entry* member_0; } ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_INCLUDE_HASH ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iterator_compare_data*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterator_compare ; 

void validate_apply_workdir(
	git_repository *repo,
	struct merge_index_entry *workdir_entries,
	size_t workdir_cnt)
{
	git_index *index;
	git_iterator *iterator;
	git_iterator_options opts = GIT_ITERATOR_OPTIONS_INIT;
	struct iterator_compare_data data = { workdir_entries, workdir_cnt };

	opts.flags |= GIT_ITERATOR_INCLUDE_HASH;

	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_iterator_for_workdir(&iterator, repo, index, NULL, &opts));

	cl_git_pass(git_iterator_foreach(iterator, iterator_compare, &data));
	cl_assert_equal_i(data.idx, data.cnt);

	git_iterator_free(iterator);
	git_index_free(index);
}