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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_STASH_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_path_exists (char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 

__attribute__((used)) static void push_three_states(void)
{
	git_oid oid;
	git_index *index;

	cl_git_mkfile("stash/zero.txt", "content\n");
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_bypath(index, "zero.txt"));
	cl_repo_commit_from_index(NULL, repo, signature, 0, "Initial commit");
	cl_assert(git_path_exists("stash/zero.txt"));
	git_index_free(index);

	cl_git_mkfile("stash/one.txt", "content\n");
	cl_git_pass(git_stash_save(
		&oid, repo, signature, "First", GIT_STASH_INCLUDE_UNTRACKED));
	cl_assert(!git_path_exists("stash/one.txt"));
	cl_assert(git_path_exists("stash/zero.txt"));

	cl_git_mkfile("stash/two.txt", "content\n");
	cl_git_pass(git_stash_save(
		&oid, repo, signature, "Second", GIT_STASH_INCLUDE_UNTRACKED));
	cl_assert(!git_path_exists("stash/two.txt"));
	cl_assert(git_path_exists("stash/zero.txt"));

	cl_git_mkfile("stash/three.txt", "content\n");
	cl_git_pass(git_stash_save(
		&oid, repo, signature, "Third", GIT_STASH_INCLUDE_UNTRACKED));
	cl_assert(!git_path_exists("stash/three.txt"));
	cl_assert(git_path_exists("stash/zero.txt"));
}