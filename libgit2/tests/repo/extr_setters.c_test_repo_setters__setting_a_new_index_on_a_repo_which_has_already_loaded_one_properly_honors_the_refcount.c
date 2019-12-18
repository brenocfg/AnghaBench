#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int val; } ;
struct TYPE_4__ {TYPE_1__ refcount; } ;
typedef  TYPE_2__ git_refcount ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_set_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * repo ; 

void test_repo_setters__setting_a_new_index_on_a_repo_which_has_already_loaded_one_properly_honors_the_refcount(void)
{
	git_index *new_index;

	cl_git_pass(git_index_open(&new_index, "./my-index"));
	cl_assert(((git_refcount *)new_index)->refcount.val == 1);

	git_repository_set_index(repo, new_index);
	cl_assert(((git_refcount *)new_index)->refcount.val == 2);

	git_repository_free(repo);
	cl_assert(((git_refcount *)new_index)->refcount.val == 1);

	git_index_free(new_index);

	/* 
	 * Ensure the cleanup method won't try to free the repo as it's already been taken care of
	 */
	repo = NULL;
}