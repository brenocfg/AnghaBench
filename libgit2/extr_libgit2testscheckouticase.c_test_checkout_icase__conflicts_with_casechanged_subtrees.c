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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_write2file (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup_resolved (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  repo ; 

void test_checkout_icase__conflicts_with_casechanged_subtrees(void)
{
	git_reference *orig_ref;
	git_object *orig, *subtrees;
	git_oid oid;
	git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

	checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;

	cl_git_pass(git_reference_lookup_resolved(&orig_ref, repo, "HEAD", 100));
	cl_git_pass(git_object_lookup(&orig, repo, git_reference_target(orig_ref), GIT_OBJECT_COMMIT));
	cl_git_pass(git_reset(repo, (git_object *)orig, GIT_RESET_HARD, NULL));

	cl_must_pass(p_mkdir("testrepo/AB", 0777));
	cl_must_pass(p_mkdir("testrepo/AB/C", 0777));
	cl_git_write2file("testrepo/AB/C/3.txt", "Foobar!\n", 8, O_RDWR|O_CREAT, 0666);

	cl_git_pass(git_reference_name_to_id(&oid, repo, "refs/heads/subtrees"));
	cl_git_pass(git_object_lookup(&subtrees, repo, &oid, GIT_OBJECT_ANY));

	cl_git_fail(git_checkout_tree(repo, subtrees, &checkout_opts));

	git_object_free(orig);
	git_object_free(subtrees);
    git_reference_free(orig_ref);
}