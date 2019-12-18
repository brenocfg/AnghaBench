#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t count; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_9__ {char* checkout_branch; int /*<<< orphan*/  remote_cb; } ;
typedef  TYPE_2__ git_clone_options ;

/* Variables and functions */
 TYPE_2__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  REFSPEC ; 
 int /*<<< orphan*/  URL ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__prefixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_reference_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_get_fetch_refspecs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  remote_single_branch ; 

void test_online_remotes__single_branch(void)
{
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	git_repository *repo;
	git_remote *remote;
	git_strarray refs;
	size_t i, count = 0;

	opts.remote_cb = remote_single_branch;
	opts.checkout_branch = "first-merge";

	cl_git_pass(git_clone(&repo, URL, "./single-branch", &opts));
	cl_git_pass(git_reference_list(&refs, repo));

	for (i = 0; i < refs.count; i++) {
		if (!git__prefixcmp(refs.strings[i], "refs/heads/"))
			count++;
	}
	cl_assert_equal_i(1, count);

	git_strarray_free(&refs);

	cl_git_pass(git_remote_lookup(&remote, repo, "origin"));
	cl_git_pass(git_remote_get_fetch_refspecs(&refs, remote));

	cl_assert_equal_i(1, refs.count);
	cl_assert_equal_s(REFSPEC, refs.strings[0]);

	git_strarray_free(&refs);
	git_remote_free(remote);
	git_repository_free(repo);
}