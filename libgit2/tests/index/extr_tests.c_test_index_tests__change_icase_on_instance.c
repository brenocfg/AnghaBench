#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_12__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  ignore_case; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 unsigned int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 int /*<<< orphan*/  TEST_INDEX_PATH ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 unsigned int git_index_caps (TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_2__*) ; 
 TYPE_1__* git_index_get_bypath (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_open (TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_set_caps (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  git_vector_verify_sorted (int /*<<< orphan*/ *) ; 

void test_index_tests__change_icase_on_instance(void)
{
	git_index *index;
	unsigned int caps;
	const git_index_entry *e;

	cl_git_pass(git_index_open(&index, TEST_INDEX_PATH));
	cl_git_pass(git_vector_verify_sorted(&index->entries));

	caps = git_index_caps(index);
	cl_git_pass(git_index_set_caps(index, caps &= ~GIT_INDEX_CAPABILITY_IGNORE_CASE));
	cl_assert_equal_i(false, index->ignore_case);
	cl_git_pass(git_vector_verify_sorted(&index->entries));
	cl_assert(e = git_index_get_bypath(index, "src/common.h", 0));
	cl_assert_equal_p(NULL, e = git_index_get_bypath(index, "SRC/Common.h", 0));
	cl_assert(e = git_index_get_bypath(index, "COPYING", 0));
	cl_assert_equal_p(NULL, e = git_index_get_bypath(index, "copying", 0));

	cl_git_pass(git_index_set_caps(index, caps | GIT_INDEX_CAPABILITY_IGNORE_CASE));
	cl_assert_equal_i(true, index->ignore_case);
	cl_git_pass(git_vector_verify_sorted(&index->entries));
	cl_assert(e = git_index_get_bypath(index, "COPYING", 0));
	cl_assert_equal_s("COPYING", e->path);
	cl_assert(e = git_index_get_bypath(index, "copying", 0));
	cl_assert_equal_s("COPYING", e->path);

	git_index_free(index);
}