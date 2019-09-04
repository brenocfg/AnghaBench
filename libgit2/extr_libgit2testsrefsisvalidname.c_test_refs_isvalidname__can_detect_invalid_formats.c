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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_is_valid_name (char*) ; 

void test_refs_isvalidname__can_detect_invalid_formats(void)
{
	cl_assert_equal_i(false, git_reference_is_valid_name("refs/tags/0.17.0^{}"));
	cl_assert_equal_i(false, git_reference_is_valid_name("TWO/LEVELS"));
	cl_assert_equal_i(false, git_reference_is_valid_name("ONE.LEVEL"));
	cl_assert_equal_i(false, git_reference_is_valid_name("HEAD/"));
	cl_assert_equal_i(false, git_reference_is_valid_name("NO_TRAILING_UNDERSCORE_"));
	cl_assert_equal_i(false, git_reference_is_valid_name("_NO_LEADING_UNDERSCORE"));
	cl_assert_equal_i(false, git_reference_is_valid_name("HEAD/aa"));
	cl_assert_equal_i(false, git_reference_is_valid_name("lower_case"));
	cl_assert_equal_i(false, git_reference_is_valid_name("/stupid/name/master"));
	cl_assert_equal_i(false, git_reference_is_valid_name("/"));
	cl_assert_equal_i(false, git_reference_is_valid_name("//"));
	cl_assert_equal_i(false, git_reference_is_valid_name(""));
	cl_assert_equal_i(false, git_reference_is_valid_name("refs/heads/sub.lock/webmatrix"));
}