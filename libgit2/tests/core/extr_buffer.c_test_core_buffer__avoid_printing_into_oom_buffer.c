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
struct TYPE_4__ {int asize; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf__oom ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 

void test_core_buffer__avoid_printing_into_oom_buffer(void)
{
	git_buf buf = GIT_BUF_INIT;

	/* Emulate OOM situation with a previous allocation */
	buf.asize = 8;
	buf.ptr = git_buf__oom;

	/*
	 * Print the same string again. As the buffer still has
	 * an `asize` of 8 due to the previous print,
	 * `ENSURE_SIZE` would not try to reallocate the array at
	 * all. As it didn't explicitly check for `git_buf__oom`
	 * in earlier versions, this would've resulted in it
	 * returning successfully and thus `git_buf_puts` would
	 * just print into the `git_buf__oom` array.
	 */
	cl_git_fail(git_buf_puts(&buf, "foobar"));
}