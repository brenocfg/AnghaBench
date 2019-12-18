#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERNATE_MALFORMED_FOLDER1 ; 
 int /*<<< orphan*/  ALTERNATE_MALFORMED_FOLDER2 ; 
 int /*<<< orphan*/  ALTERNATE_MALFORMED_FOLDER3 ; 
 int /*<<< orphan*/  ALTERNATE_NOT_FOUND_FOLDER ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 TYPE_1__ ceiling_dirs ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discovered ; 
 int /*<<< orphan*/  git_repository_discover (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_repo_discover__discovering_repository_with_malformed_alternative_gitdir_fails(void)
{
	cl_git_fail(git_repository_discover(&discovered, ALTERNATE_MALFORMED_FOLDER1, 0, ceiling_dirs.ptr));
	cl_git_fail(git_repository_discover(&discovered, ALTERNATE_MALFORMED_FOLDER2, 0, ceiling_dirs.ptr));
	cl_git_fail(git_repository_discover(&discovered, ALTERNATE_MALFORMED_FOLDER3, 0, ceiling_dirs.ptr));
	cl_assert_equal_i(GIT_ENOTFOUND, git_repository_discover(&discovered, ALTERNATE_NOT_FOUND_FOLDER, 0, ceiling_dirs.ptr));
}