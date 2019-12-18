#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  _alloc_size; int /*<<< orphan*/  _cmp; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 TYPE_1__ GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_dup (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_1__*,int*) ; 

void test_core_vector__dup_empty_vector(void)
{
	git_vector v = GIT_VECTOR_INIT;
	git_vector dup = GIT_VECTOR_INIT;
	int dummy;

	cl_assert_equal_i(0, v.length);

	cl_git_pass(git_vector_dup(&dup, &v, v._cmp));
	cl_assert_equal_i(0, dup._alloc_size);
	cl_assert_equal_i(0, dup.length);

	cl_git_pass(git_vector_insert(&dup, &dummy));
	cl_assert_equal_i(8, dup._alloc_size);
	cl_assert_equal_i(1, dup.length);

	git_vector_free(&dup);
}