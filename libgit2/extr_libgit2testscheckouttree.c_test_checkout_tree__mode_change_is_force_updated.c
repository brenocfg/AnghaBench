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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  assert_on_branch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert_status_entrycount (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_chmod_supported () ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  g_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_chmod (char*,int) ; 

void test_checkout_tree__mode_change_is_force_updated(void)
{
	git_index *index;
	git_reference *head;
	git_object *obj;

	if (!cl_is_chmod_supported())
		clar__skip();

	assert_on_branch(g_repo, "master");
	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_repository_head(&head, g_repo));
	cl_git_pass(git_reference_peel(&obj, head, GIT_OBJECT_COMMIT));

	cl_git_pass(git_reset(g_repo, obj, GIT_RESET_HARD, NULL));
	assert_status_entrycount(g_repo, 0);

	/* update the mode on-disk */
	cl_must_pass(p_chmod("testrepo/README", 0755));

	assert_status_entrycount(g_repo, 1);
	cl_git_pass(git_checkout_tree(g_repo, obj, &g_opts));
	assert_status_entrycount(g_repo, 0);

	/* update the mode on-disk and in the index */
	cl_must_pass(p_chmod("testrepo/README", 0755));
	cl_must_pass(git_index_add_bypath(index, "README"));

	cl_git_pass(git_index_write(index));
	assert_status_entrycount(g_repo, 1);

	cl_git_pass(git_checkout_tree(g_repo, obj, &g_opts));
	cl_git_pass(git_index_write(index));

	assert_status_entrycount(g_repo, 0);

	git_object_free(obj);
	git_reference_free(head);
	git_index_free(index);
}