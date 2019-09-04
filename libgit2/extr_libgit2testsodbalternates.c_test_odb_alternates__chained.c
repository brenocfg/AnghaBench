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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_linked_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * paths ; 
 int /*<<< orphan*/  repo ; 

void test_odb_alternates__chained(void)
{
	git_commit *commit;
	git_oid oid;

	/* Set the alternate A -> testrepo.git */
	init_linked_repo(paths[0], cl_fixture("testrepo.git"));

	/* Set the alternate B -> A */
	init_linked_repo(paths[1], paths[0]);

	/* Now load B and see if we can find an object from testrepo.git */
	cl_git_pass(git_repository_open(&repo, paths[1]));
	git_oid_fromstr(&oid, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	cl_git_pass(git_commit_lookup(&commit, repo, &oid));
	git_commit_free(commit);
	git_repository_free(repo);
}