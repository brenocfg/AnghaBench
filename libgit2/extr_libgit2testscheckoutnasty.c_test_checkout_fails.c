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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_8__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_name ; 

__attribute__((used)) static void test_checkout_fails(const char *refname, const char *filename)
{
	git_oid commit_id;
	git_commit *commit;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_buf path = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&path, repo_name, filename));

	cl_git_pass(git_reference_name_to_id(&commit_id, repo, refname));
	cl_git_pass(git_commit_lookup(&commit, repo, &commit_id));

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_fail(git_checkout_tree(repo, (const git_object *)commit, &opts));
	cl_assert(!git_path_exists(path.ptr));

	git_commit_free(commit);
	git_buf_dispose(&path);
}