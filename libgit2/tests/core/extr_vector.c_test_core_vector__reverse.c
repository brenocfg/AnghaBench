#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_p (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  git_vector_reverse (int /*<<< orphan*/ *) ; 

void test_core_vector__reverse(void)
{
	git_vector v = GIT_VECTOR_INIT;
	size_t i;

	void *in1[] = {(void *) 0x0, (void *) 0x1, (void *) 0x2, (void *) 0x3};
	void *out1[] = {(void *) 0x3, (void *) 0x2, (void *) 0x1, (void *) 0x0};

	void *in2[] = {(void *) 0x0, (void *) 0x1, (void *) 0x2, (void *) 0x3, (void *) 0x4};
	void *out2[] = {(void *) 0x4, (void *) 0x3, (void *) 0x2, (void *) 0x1, (void *) 0x0};

	for (i = 0; i < 4; i++)
		cl_git_pass(git_vector_insert(&v, in1[i]));

	git_vector_reverse(&v);

	for (i = 0; i < 4; i++)
		cl_assert_equal_p(out1[i], git_vector_get(&v, i));

	git_vector_clear(&v);
	for (i = 0; i < 5; i++)
		cl_git_pass(git_vector_insert(&v, in2[i]));

	git_vector_reverse(&v);

	for (i = 0; i < 5; i++)
		cl_assert_equal_p(out2[i], git_vector_get(&v, i));

	git_vector_free(&v);
}