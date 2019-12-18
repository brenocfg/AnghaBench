#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_OFS_DELTA ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_odb_hashfile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_hashfile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 

void test_repo_hashfile__simple(void)
{
	git_oid a, b;
	git_buf full = GIT_BUF_INIT;

	/* hash with repo relative path */
	cl_git_pass(git_odb_hashfile(&a, "status/current_file", GIT_OBJECT_BLOB));
	cl_git_pass(git_repository_hashfile(&b, _repo, "current_file", GIT_OBJECT_BLOB, NULL));
	cl_assert_equal_oid(&a, &b);

	cl_git_pass(git_buf_joinpath(&full, git_repository_workdir(_repo), "current_file"));

	/* hash with full path */
	cl_git_pass(git_odb_hashfile(&a, full.ptr, GIT_OBJECT_BLOB));
	cl_git_pass(git_repository_hashfile(&b, _repo, full.ptr, GIT_OBJECT_BLOB, NULL));
	cl_assert_equal_oid(&a, &b);

	/* hash with invalid type */
	cl_git_fail(git_odb_hashfile(&a, full.ptr, GIT_OBJECT_ANY));
	cl_git_fail(git_repository_hashfile(&b, _repo, full.ptr, GIT_OBJECT_OFS_DELTA, NULL));

	git_buf_dispose(&full);
}