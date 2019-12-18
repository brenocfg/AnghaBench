#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {char const* start; char const* end; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_IGNORE_CASE ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_iterator_advance (TYPE_2__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_current (TYPE_2__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_wd_first_through_third_range(
	git_repository *repo, const char *start, const char *end)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	const git_index_entry *entry;
	int error, idx;
	static const char *expected[] = { "FIRST", "second", "THIRD", NULL };

	i_opts.flags = GIT_ITERATOR_IGNORE_CASE;
	i_opts.start = start;
	i_opts.end = end;

	cl_git_pass(git_iterator_for_workdir(
		&i, repo, NULL, NULL, &i_opts));
	cl_git_pass(git_iterator_current(&entry, i));

	for (idx = 0; entry != NULL; ++idx) {
		cl_assert_equal_s(expected[idx], entry->path);

		error = git_iterator_advance(&entry, i);
		cl_assert(!error || error == GIT_ITEROVER);
	}

	cl_assert(expected[idx] == NULL);

	git_iterator_free(i);
}