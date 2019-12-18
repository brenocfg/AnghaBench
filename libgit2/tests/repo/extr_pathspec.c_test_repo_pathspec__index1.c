#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  strings; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_pathspec_match_list ;
typedef  int /*<<< orphan*/  git_pathspec ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int GIT_PATHSPEC_FIND_FAILURES ; 
 int GIT_PATHSPEC_IGNORE_CASE ; 
 int GIT_PATHSPEC_USE_CASE ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_list_failed_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_new (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str1 ; 

void test_repo_pathspec__index1(void)
{
	/* Currently the USE_CASE and IGNORE_CASE flags don't work on the
	 * index because the index sort order for the index iterator is
	 * set by the index itself.  I think the correct fix is for the
	 * index not to embed a global sort order but to support traversal
	 * in either case sensitive or insensitive order in a stateless
	 * manner.
	 *
	 * Anyhow, as it is, there is no point in doing this test.
	 */
#if 0
	git_index *idx;
	git_strarray s;
	git_pathspec *ps;
	git_pathspec_match_list *m;

	cl_git_pass(git_repository_index(&idx, g_repo));

	/* { "*_FILE", "NEW_FILE", "GARBAGE" } */
	s.strings = str1; s.count = ARRAY_SIZE(str1);
	cl_git_pass(git_pathspec_new(&ps, &s));

	cl_git_pass(git_pathspec_match_index(&m, idx,
		GIT_PATHSPEC_USE_CASE, ps));
	cl_assert_equal_sz(0, git_pathspec_match_list_entrycount(m));
	cl_assert_equal_sz(0, git_pathspec_match_list_failed_entrycount(m));
	git_pathspec_match_list_free(m);

	cl_git_pass(git_pathspec_match_index(&m, idx,
		GIT_PATHSPEC_USE_CASE | GIT_PATHSPEC_FIND_FAILURES, ps));
	cl_assert_equal_sz(0, git_pathspec_match_list_entrycount(m));
	cl_assert_equal_sz(3, git_pathspec_match_list_failed_entrycount(m));
	git_pathspec_match_list_free(m);

	cl_git_pass(git_pathspec_match_index(&m, idx,
		GIT_PATHSPEC_IGNORE_CASE | GIT_PATHSPEC_FIND_FAILURES, ps));
	cl_assert_equal_sz(10, git_pathspec_match_list_entrycount(m));
	cl_assert_equal_sz(2, git_pathspec_match_list_failed_entrycount(m));
	git_pathspec_match_list_free(m);

	git_pathspec_free(ps);
	git_index_free(idx);
#endif
}