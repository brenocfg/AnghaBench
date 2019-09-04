#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_6__ {scalar_t__ index_updated; } ;
typedef  TYPE_2__ git_diff_generated ;
struct TYPE_5__ {int flags; } ;
struct TYPE_7__ {TYPE_1__ opts; } ;
typedef  TYPE_3__ git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FROM_ITERATORS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GIT_DIFF_UPDATE_INDEX ; 
 int /*<<< orphan*/  GIT_ITERATOR_DONT_AUTOEXPAND ; 
 int /*<<< orphan*/  GIT_ITERATOR_INCLUDE_CONFLICTS ; 
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  a_opts ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  b_opts ; 
 int diff_load_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_diff_index_to_workdir(
	git_diff **out,
	git_repository *repo,
	git_index *index,
	const git_diff_options *opts)
{
	git_diff *diff = NULL;
	int error = 0;

	assert(out && repo);

	*out = NULL;

	if (!index && (error = diff_load_index(&index, repo)) < 0)
		return error;

	DIFF_FROM_ITERATORS(
		git_iterator_for_index(&a, repo, index, &a_opts),
		GIT_ITERATOR_INCLUDE_CONFLICTS,

		git_iterator_for_workdir(&b, repo, index, NULL, &b_opts),
		GIT_ITERATOR_DONT_AUTOEXPAND
	);

	if (!error && (diff->opts.flags & GIT_DIFF_UPDATE_INDEX) != 0 &&
		((git_diff_generated *)diff)->index_updated)
		error = git_index_write(index);

	if (!error)
		*out = diff;

	return error;
}