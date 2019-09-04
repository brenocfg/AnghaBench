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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 scalar_t__ p_fsync__cnt ; 

void test_odb_loose__fsync_obeys_repo_setting(void)
{
	git_repository *repo;
	git_odb *odb;
	git_oid oid;

	cl_git_pass(git_repository_init(&repo, "test-objects", 1));
	cl_git_pass(git_repository_odb__weakptr(&odb, repo));
	cl_git_pass(git_odb_write(&oid, odb, "No fsync here\n", 14, GIT_OBJECT_BLOB));
	cl_assert(p_fsync__cnt == 0);
	git_repository_free(repo);

	cl_git_pass(git_repository_open(&repo, "test-objects"));
	cl_repo_set_bool(repo, "core.fsyncObjectFiles", true);
	cl_git_pass(git_repository_odb__weakptr(&odb, repo));
	cl_git_pass(git_odb_write(&oid, odb, "Now fsync\n", 10, GIT_OBJECT_BLOB));
	cl_assert(p_fsync__cnt > 0);
	git_repository_free(repo);
}