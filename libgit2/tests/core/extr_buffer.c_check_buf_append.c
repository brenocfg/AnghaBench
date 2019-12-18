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
struct TYPE_8__ {int /*<<< orphan*/  asize; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char const*) ; 

__attribute__((used)) static void
check_buf_append(
	const char* data_a,
	const char* data_b,
	const char* expected_data,
	size_t expected_size,
	size_t expected_asize)
{
	git_buf tgt = GIT_BUF_INIT;

	git_buf_sets(&tgt, data_a);
	cl_assert(git_buf_oom(&tgt) == 0);
	git_buf_puts(&tgt, data_b);
	cl_assert(git_buf_oom(&tgt) == 0);
	cl_assert_equal_s(expected_data, git_buf_cstr(&tgt));
	cl_assert_equal_i(tgt.size, expected_size);
	if (expected_asize > 0)
		cl_assert_equal_i(tgt.asize, expected_asize);

	git_buf_dispose(&tgt);
}