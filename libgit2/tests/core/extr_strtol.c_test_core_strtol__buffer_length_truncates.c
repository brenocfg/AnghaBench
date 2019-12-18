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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strntol32 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git__strntol64 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int) ; 

void test_core_strtol__buffer_length_truncates(void)
{
	int32_t i32;
	int64_t i64;

	cl_git_pass(git__strntol32(&i32, "11", 1, NULL, 10));
	cl_assert_equal_i(i32, 1);

	cl_git_pass(git__strntol64(&i64, "11", 1, NULL, 10));
	cl_assert_equal_i(i64, 1);
}