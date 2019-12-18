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
 int /*<<< orphan*/  add_invalid_filename (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_index_tests__add_invalid_filename(void)
{
	git_repository *repo;

	p_mkdir("invalid", 0700);

	cl_git_pass(git_repository_init(&repo, "./invalid", 0));
	cl_must_pass(p_mkdir("./invalid/subdir", 0777));

	/* cl_git_mkfile() needs the dir to exist */
	if (!git_path_exists("./invalid/.GIT"))
		cl_must_pass(p_mkdir("./invalid/.GIT", 0777));
	if (!git_path_exists("./invalid/.GiT"))
		cl_must_pass(p_mkdir("./invalid/.GiT", 0777));

	add_invalid_filename(repo, ".git/hello");
	add_invalid_filename(repo, ".GIT/hello");
	add_invalid_filename(repo, ".GiT/hello");
	add_invalid_filename(repo, "./.git/hello");
	add_invalid_filename(repo, "./foo");
	add_invalid_filename(repo, "./bar");
	add_invalid_filename(repo, "subdir/../bar");

	git_repository_free(repo);

	cl_fixture_cleanup("invalid");
}