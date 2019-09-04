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

/* Variables and functions */

void test_checkout_nasty__only_looks_like_a_git_shortname(void)
{
#ifdef GIT_WIN32
	git_oid commit_id;
	git_commit *commit;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	cl_must_pass(p_rename("nasty/.git", "nasty/_temp"));
	cl_git_write2file("nasty/git~1", "", 0, O_RDWR|O_CREAT, 0666);
	cl_must_pass(p_rename("nasty/_temp", "nasty/.git"));

	cl_git_pass(git_reference_name_to_id(&commit_id, repo, "refs/heads/git_tilde3"));
	cl_git_pass(git_commit_lookup(&commit, repo, &commit_id));

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_checkout_tree(repo, (const git_object *)commit, &opts));
	cl_assert(git_path_exists("nasty/git~3/foobar"));

	git_commit_free(commit);
#endif
}