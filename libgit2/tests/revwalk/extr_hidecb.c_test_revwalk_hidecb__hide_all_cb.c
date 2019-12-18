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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  _head_id ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_add_hide_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hide_every_commit_cb ; 

void test_revwalk_hidecb__hide_all_cb(void)
{
	git_revwalk *walk;
	git_oid id;

	cl_git_pass(git_revwalk_new(&walk, _repo));
	cl_git_pass(git_revwalk_add_hide_cb(walk, hide_every_commit_cb, NULL));
	cl_git_pass(git_revwalk_push(walk, &_head_id));

	/* First call to git_revwalk_next should return GIT_ITEROVER */
	cl_assert_equal_i(GIT_ITEROVER, git_revwalk_next(&id, walk));

	git_revwalk_free(walk);
}