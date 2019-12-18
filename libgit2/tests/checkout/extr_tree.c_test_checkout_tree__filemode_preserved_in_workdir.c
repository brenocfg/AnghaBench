#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_PERMS_IS_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  read_filemode (char*) ; 

void test_checkout_tree__filemode_preserved_in_workdir(void)
{
#ifndef GIT_WIN32
	git_oid executable_oid;
	git_commit *commit;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	/* test a freshly added executable */
	cl_git_pass(git_oid_fromstr(&executable_oid, "afe4393b2b2a965f06acf2ca9658eaa01e0cd6b6"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &executable_oid));

	cl_git_pass(git_checkout_tree(g_repo, (const git_object *)commit, &opts));
	cl_assert(GIT_PERMS_IS_EXEC(read_filemode("executable.txt")));

	git_commit_free(commit);


	/* Now start with a commit which has a text file */
	cl_git_pass(git_oid_fromstr(&executable_oid, "cf80f8de9f1185bf3a05f993f6121880dd0cfbc9"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &executable_oid));

	cl_git_pass(git_checkout_tree(g_repo, (const git_object *)commit, &opts));
	cl_assert(!GIT_PERMS_IS_EXEC(read_filemode("a/b.txt")));

	git_commit_free(commit);


	/* And then check out to a commit which converts the text file to an executable */
	cl_git_pass(git_oid_fromstr(&executable_oid, "144344043ba4d4a405da03de3844aa829ae8be0e"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &executable_oid));

	cl_git_pass(git_checkout_tree(g_repo, (const git_object *)commit, &opts));
	cl_assert(GIT_PERMS_IS_EXEC(read_filemode("a/b.txt")));

	git_commit_free(commit);


	/* Finally, check out the text file again and check that the exec bit is cleared */
	cl_git_pass(git_oid_fromstr(&executable_oid, "cf80f8de9f1185bf3a05f993f6121880dd0cfbc9"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &executable_oid));

	cl_git_pass(git_checkout_tree(g_repo, (const git_object *)commit, &opts));
	cl_assert(!GIT_PERMS_IS_EXEC(read_filemode("a/b.txt")));

	git_commit_free(commit);
#else
	cl_skip();
#endif
}