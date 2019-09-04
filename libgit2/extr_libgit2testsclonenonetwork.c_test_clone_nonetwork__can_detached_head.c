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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 char* cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_options ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_detached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

void test_clone_nonetwork__can_detached_head(void)
{
	git_object *obj;
	git_repository *cloned;
	git_reference *cloned_head;

	cl_git_pass(git_clone(&g_repo, cl_git_fixture_url("testrepo.git"), "./foo", &g_options));

	cl_git_pass(git_revparse_single(&obj, g_repo, "master~1"));
	cl_git_pass(git_repository_set_head_detached(g_repo, git_object_id(obj)));

	cl_git_pass(git_clone(&cloned, "./foo", "./foo1", &g_options));

	cl_assert(git_repository_head_detached(cloned));

	cl_git_pass(git_repository_head(&cloned_head, cloned));
	cl_assert_equal_oid(git_object_id(obj), git_reference_target(cloned_head));

	git_object_free(obj);
	git_reference_free(cloned_head);
	git_repository_free(cloned);

	cl_fixture_cleanup("./foo1");
}