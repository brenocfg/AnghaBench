#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_ITERATOR_IGNORE_CASE ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  expected_index_ci ; 
 int /*<<< orphan*/  expected_index_cs ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_iterator_test (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_iterator_index__case_folding(void)
{
	git_buf path = GIT_BUF_INIT;
	int fs_is_ci = 0;

	cl_git_pass(git_buf_joinpath(&path, cl_fixture("icase"), ".gitted/CoNfIg"));
	fs_is_ci = git_path_exists(path.ptr);
	git_buf_dispose(&path);

	index_iterator_test(
		"icase", NULL, NULL, 0, ARRAY_SIZE(expected_index_cs),
		fs_is_ci ? expected_index_ci : expected_index_cs, NULL);

	cl_git_sandbox_cleanup();

	index_iterator_test(
		"icase", NULL, NULL, GIT_ITERATOR_IGNORE_CASE,
		ARRAY_SIZE(expected_index_ci), expected_index_ci, NULL);

	cl_git_sandbox_cleanup();

	index_iterator_test(
		"icase", NULL, NULL, GIT_ITERATOR_DONT_IGNORE_CASE,
		ARRAY_SIZE(expected_index_cs), expected_index_cs, NULL);
}