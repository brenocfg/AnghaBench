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
 int /*<<< orphan*/  GIT_PATH_REJECT_DOT_GIT_HFS ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isvalid (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_path_core__isvalid_dotgit_with_hfs_ignorables(void)
{
	cl_assert_equal_b(false, git_path_isvalid(NULL, ".git", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, ".git\xe2\x80\x8c", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, ".gi\xe2\x80\x8dT", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, ".g\xe2\x80\x8eIt", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, ".\xe2\x80\x8fgIt", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "\xe2\x80\xaa.gIt", 0, GIT_PATH_REJECT_DOT_GIT_HFS));

	cl_assert_equal_b(false, git_path_isvalid(NULL, "\xe2\x80\xab.\xe2\x80\xacG\xe2\x80\xadI\xe2\x80\xaet", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "\xe2\x81\xab.\xe2\x80\xaaG\xe2\x81\xabI\xe2\x80\xact", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "\xe2\x81\xad.\xe2\x80\xaeG\xef\xbb\xbfIT", 0, GIT_PATH_REJECT_DOT_GIT_HFS));

	cl_assert_equal_b(true, git_path_isvalid(NULL, ".", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".g", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".gi", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, " .git", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "..git\xe2\x80\x8c", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".gi\xe2\x80\x8dT.", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".g\xe2\x80It", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".\xe2gIt", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "\xe2\x80\xaa.gi", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".gi\x80\x8dT", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".gi\x8dT", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".g\xe2i\x80T\x8e", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".git\xe2\x80\xbf", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, ".git\xe2\xab\x81", 0, GIT_PATH_REJECT_DOT_GIT_HFS));
}