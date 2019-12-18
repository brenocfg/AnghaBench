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
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  write_invalid_filename (int /*<<< orphan*/ *,char*) ; 

void test_index_tests__write_invalid_filename(void)
{
	git_repository *repo;

	p_mkdir("invalid", 0700);

	cl_git_pass(git_repository_init(&repo, "./invalid", 0));

	write_invalid_filename(repo, ".git/hello");
	write_invalid_filename(repo, ".GIT/hello");
	write_invalid_filename(repo, ".GiT/hello");
	write_invalid_filename(repo, "./.git/hello");
	write_invalid_filename(repo, "./foo");
	write_invalid_filename(repo, "./bar");
	write_invalid_filename(repo, "foo/../bar");

	git_repository_free(repo);

	cl_fixture_cleanup("invalid");
}