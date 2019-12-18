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
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  create_fake_stash_reference_and_reflog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_object_inrepo (char*,char*,int /*<<< orphan*/ *) ; 

void test_refs_revparse__reflog_of_a_ref_under_refs(void)
{
	git_repository *repo = cl_git_sandbox_init("testrepo.git");

	test_object_inrepo("refs/fakestash", NULL, repo);

	create_fake_stash_reference_and_reflog(repo);

	/*
	 * $ git reflog -1 refs/fakestash
	 * a65fedf refs/fakestash@{0}: commit: checking in
	 *
	 * $ git reflog -1 refs/fakestash@{0}
	 * a65fedf refs/fakestash@{0}: commit: checking in
	 *
	 * $ git reflog -1 fakestash
	 * a65fedf fakestash@{0}: commit: checking in
	 *
	 * $ git reflog -1 fakestash@{0}
	 * a65fedf fakestash@{0}: commit: checking in
	 */
	test_object_inrepo("refs/fakestash", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750", repo);
	test_object_inrepo("refs/fakestash@{0}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750", repo);
	test_object_inrepo("fakestash", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750", repo);
	test_object_inrepo("fakestash@{0}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750", repo);

	cl_git_sandbox_cleanup();
}