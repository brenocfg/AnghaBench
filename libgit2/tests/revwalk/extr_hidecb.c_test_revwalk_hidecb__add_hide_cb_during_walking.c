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
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int git_revwalk_add_hide_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_revwalk_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hide_none_cb ; 

void test_revwalk_hidecb__add_hide_cb_during_walking(void)
{
	git_revwalk *walk;
	git_oid id;
	int error;

	cl_git_pass(git_revwalk_new(&walk, _repo));
	cl_git_pass(git_revwalk_push(walk, &_head_id));

	/* Start walking without adding hide callback */
	cl_git_pass(git_revwalk_next(&id, walk));

	/* Now add hide callback */
	cl_git_pass(git_revwalk_add_hide_cb(walk, hide_none_cb, NULL));

	/* walk should be reset */
	error = git_revwalk_next(&id, walk);
	cl_assert_equal_i(error, GIT_ITEROVER);

	git_revwalk_free(walk);
}