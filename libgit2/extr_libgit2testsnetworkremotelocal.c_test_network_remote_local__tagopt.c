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
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_4__ {int /*<<< orphan*/  download_tags; } ;
typedef  TYPE_1__ git_fetch_options ;

/* Variables and functions */
 TYPE_1__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_ALL ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_AUTO ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_path_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote ; 
 int /*<<< orphan*/  repo ; 

void test_network_remote_local__tagopt(void)
{
	git_reference *ref;
	git_fetch_options fetch_opts = GIT_FETCH_OPTIONS_INIT;

	cl_git_pass(git_remote_create(&remote, repo, "tagopt", cl_git_path_url(cl_fixture("testrepo.git"))));
	fetch_opts.download_tags = GIT_REMOTE_DOWNLOAD_TAGS_ALL;
	cl_git_pass(git_remote_fetch(remote, NULL, &fetch_opts, NULL));

	cl_git_pass(git_reference_lookup(&ref, repo, "refs/remotes/tagopt/master"));
	git_reference_free(ref);
	cl_git_pass(git_reference_lookup(&ref, repo, "refs/tags/hard_tag"));
	git_reference_free(ref);

	fetch_opts.download_tags = GIT_REMOTE_DOWNLOAD_TAGS_AUTO;
	cl_git_pass(git_remote_fetch(remote, NULL, &fetch_opts, NULL));
	cl_git_pass(git_reference_lookup(&ref, repo, "refs/remotes/tagopt/master"));
	git_reference_free(ref);
}