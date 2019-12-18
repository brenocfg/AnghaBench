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

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  write_invalid_filename (int /*<<< orphan*/ *,char*) ; 

void test_index_tests__honors_protect_filesystems(void)
{
	git_repository *repo;

	p_mkdir("invalid", 0700);

	cl_git_pass(git_repository_init(&repo, "./invalid", 0));

	cl_repo_set_bool(repo, "core.protectHFS", true);
	cl_repo_set_bool(repo, "core.protectNTFS", true);

	write_invalid_filename(repo, ".git./hello");
	write_invalid_filename(repo, ".git\xe2\x80\xad/hello");
	write_invalid_filename(repo, "git~1/hello");
	write_invalid_filename(repo, ".git\xe2\x81\xaf/hello");

	git_repository_free(repo);

	cl_fixture_cleanup("invalid");
}