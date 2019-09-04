#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 unsigned int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 int /*<<< orphan*/  TEST_INDEX_PATH ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 unsigned int git_index_caps (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_get_bypath (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_open (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_index_set_caps (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  git_vector_verify_sorted (int /*<<< orphan*/ *) ; 

void test_index_tests__reload_while_ignoring_case(void)
{
	git_index *index;
	unsigned int caps;

	cl_git_pass(git_index_open(&index, TEST_INDEX_PATH));
	cl_git_pass(git_vector_verify_sorted(&index->entries));

	caps = git_index_caps(index);
	cl_git_pass(git_index_set_caps(index, caps &= ~GIT_INDEX_CAPABILITY_IGNORE_CASE));
	cl_git_pass(git_index_read(index, true));
	cl_git_pass(git_vector_verify_sorted(&index->entries));
	cl_assert(git_index_get_bypath(index, ".HEADER", 0));
	cl_assert_equal_p(NULL, git_index_get_bypath(index, ".header", 0));

	cl_git_pass(git_index_set_caps(index, caps | GIT_INDEX_CAPABILITY_IGNORE_CASE));
	cl_git_pass(git_index_read(index, true));
	cl_git_pass(git_vector_verify_sorted(&index->entries));
	cl_assert(git_index_get_bypath(index, ".HEADER", 0));
	cl_assert(git_index_get_bypath(index, ".header", 0));

	git_index_free(index);
}