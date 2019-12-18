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
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {char const* start; char const* end; scalar_t__ flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_set_caps (int /*<<< orphan*/ *,int) ; 
 int git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int git_iterator_ignore_case (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_index_range(
	git_repository *repo,
	const char *start,
	const char *end,
	bool ignore_case,
	int expected_count)
{
	git_index *index;
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	int error, count, caps;
	bool is_ignoring_case;

	cl_git_pass(git_repository_index(&index, repo));

	caps = git_index_caps(index);
	is_ignoring_case = ((caps & GIT_INDEX_CAPABILITY_IGNORE_CASE) != 0);

	if (ignore_case != is_ignoring_case)
		cl_git_pass(git_index_set_caps(index, caps ^ GIT_INDEX_CAPABILITY_IGNORE_CASE));

	i_opts.flags = 0;
	i_opts.start = start;
	i_opts.end = end;

	cl_git_pass(git_iterator_for_index(&i, repo, index, &i_opts));

	cl_assert(git_iterator_ignore_case(i) == ignore_case);

	for (count = 0; !(error = git_iterator_advance(NULL, i)); ++count)
		/* count em up */;

	cl_assert_equal_i(GIT_ITEROVER, error);
	cl_assert_equal_i(expected_count, count);

	git_iterator_free(i);
	git_index_free(index);
}