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
typedef  int /*<<< orphan*/  git_thread ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_sz (int,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  git_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  git_thread_join (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  return_normally ; 

void test_threads_basic__exit(void)
{
#ifndef GIT_THREADS
	clar__skip();
#else
	git_thread thread;
	void *result;

	/* Ensure that the return value of the threadproc is returned. */
	cl_git_pass(git_thread_create(&thread, return_normally, (void *)424242));
	cl_git_pass(git_thread_join(&thread, &result));
	cl_assert_equal_sz(424242, (size_t)result);

	/* Ensure that the return value of `git_thread_exit` is returned. */
	cl_git_pass(git_thread_create(&thread, return_normally, (void *)232323));
	cl_git_pass(git_thread_join(&thread, &result));
	cl_assert_equal_sz(232323, (size_t)result);
#endif
}