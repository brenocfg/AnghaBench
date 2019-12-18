#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  SUB_REPOSITORY_FOLDER ; 
 int /*<<< orphan*/  SUB_REPOSITORY_FOLDER_SUB ; 
 int /*<<< orphan*/  SUB_REPOSITORY_FOLDER_SUB_SUB ; 
 int /*<<< orphan*/  SUB_REPOSITORY_FOLDER_SUB_SUB_SUB ; 
 int /*<<< orphan*/  SUB_REPOSITORY_GITDIR ; 
 int /*<<< orphan*/  append_ceiling_dir (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ ceiling_dirs ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discovered ; 
 int /*<<< orphan*/  ensure_repository_discover (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_discover (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_repo_discover__other_ceiling(void)
{
	append_ceiling_dir(&ceiling_dirs, SUB_REPOSITORY_FOLDER);

	/* this must pass as ceiling_directories cannot predent the current
	 * working directory to be checked */
	ensure_repository_discover(SUB_REPOSITORY_FOLDER, ceiling_dirs.ptr, SUB_REPOSITORY_GITDIR);

	cl_assert_equal_i(GIT_ENOTFOUND, git_repository_discover(&discovered, SUB_REPOSITORY_FOLDER_SUB, 0, ceiling_dirs.ptr));
	cl_assert_equal_i(GIT_ENOTFOUND, git_repository_discover(&discovered, SUB_REPOSITORY_FOLDER_SUB_SUB, 0, ceiling_dirs.ptr));
	cl_assert_equal_i(GIT_ENOTFOUND, git_repository_discover(&discovered, SUB_REPOSITORY_FOLDER_SUB_SUB_SUB, 0, ceiling_dirs.ptr));
}