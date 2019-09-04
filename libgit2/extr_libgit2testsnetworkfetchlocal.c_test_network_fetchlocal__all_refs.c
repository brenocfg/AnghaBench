#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** member_0; int member_1; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_create_anonymous (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 

void test_network_fetchlocal__all_refs(void)
{
	git_repository *repo;
	git_remote *remote;
	git_reference *ref;
	char *allrefs = "+refs/*:refs/*";
	git_strarray refspecs = {
		&allrefs,
		1,
	};

	cl_git_pass(git_repository_init(&repo, "./foo.git", true));
	cl_git_pass(git_remote_create_anonymous(&remote, repo, cl_git_fixture_url("testrepo.git")));
	cl_git_pass(git_remote_fetch(remote, &refspecs, NULL, NULL));

	cl_git_pass(git_reference_lookup(&ref, repo, "refs/remotes/test/master"));
	git_reference_free(ref);

	cl_git_pass(git_reference_lookup(&ref, repo, "refs/tags/test"));
	git_reference_free(ref);

	git_remote_free(remote);
	git_repository_free(repo);
	cl_fixture_cleanup("./foo.git");
}