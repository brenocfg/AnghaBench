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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_stash_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_three_states () ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  retrieve_top_stash_id (int /*<<< orphan*/ *) ; 

void test_stash_drop__dropping_the_top_stash_updates_the_stash_reference(void)
{
	git_object *next_top_stash;
	git_oid oid;

	push_three_states();

	retrieve_top_stash_id(&oid);

	cl_git_pass(git_revparse_single(&next_top_stash, repo, "stash@{1}"));
	cl_assert(git_oid_cmp(&oid, git_object_id(next_top_stash)));

	cl_git_pass(git_stash_drop(repo, 0));

	retrieve_top_stash_id(&oid);

	cl_assert_equal_oid(&oid, git_object_id(next_top_stash));

	git_object_free(next_top_stash);
}