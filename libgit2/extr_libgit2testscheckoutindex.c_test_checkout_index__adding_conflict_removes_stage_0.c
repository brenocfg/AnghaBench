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
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  add_conflict (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_get_bypath (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_checkout_index__adding_conflict_removes_stage_0(void)
{
	git_index *new_index, *index;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	cl_git_pass(git_index_new(&new_index));

	add_conflict(new_index, "new.txt");
	cl_git_pass(git_checkout_index(g_repo, new_index, &opts));

	cl_git_pass(git_repository_index(&index, g_repo));

	cl_assert(git_index_get_bypath(index, "new.txt", 0) == NULL);
	cl_assert(git_index_get_bypath(index, "new.txt", 1) != NULL);
	cl_assert(git_index_get_bypath(index, "new.txt", 2) != NULL);
	cl_assert(git_index_get_bypath(index, "new.txt", 3) != NULL);

	git_index_free(index);
	git_index_free(new_index);
}