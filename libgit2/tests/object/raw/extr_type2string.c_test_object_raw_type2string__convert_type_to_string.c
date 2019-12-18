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
 int GIT_OBJECT_BLOB ; 
 int GIT_OBJECT_COMMIT ; 
 int GIT_OBJECT_INVALID ; 
 int GIT_OBJECT_OFS_DELTA ; 
 int GIT_OBJECT_REF_DELTA ; 
 int GIT_OBJECT_TAG ; 
 int GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_type2string (int) ; 

void test_object_raw_type2string__convert_type_to_string(void)
{
	cl_assert_equal_s(git_object_type2string(GIT_OBJECT_INVALID), "");
	cl_assert_equal_s(git_object_type2string(0), ""); /* EXT1 */
	cl_assert_equal_s(git_object_type2string(GIT_OBJECT_COMMIT), "commit");
	cl_assert_equal_s(git_object_type2string(GIT_OBJECT_TREE), "tree");
	cl_assert_equal_s(git_object_type2string(GIT_OBJECT_BLOB), "blob");
	cl_assert_equal_s(git_object_type2string(GIT_OBJECT_TAG), "tag");
	cl_assert_equal_s(git_object_type2string(5), ""); /* EXT2 */
	cl_assert_equal_s(git_object_type2string(GIT_OBJECT_OFS_DELTA), "OFS_DELTA");
	cl_assert_equal_s(git_object_type2string(GIT_OBJECT_REF_DELTA), "REF_DELTA");

	cl_assert_equal_s(git_object_type2string(-2), "");
	cl_assert_equal_s(git_object_type2string(8), "");
	cl_assert_equal_s(git_object_type2string(1234), "");
}