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
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  GIT_DIRECTION_PUSH ; 
 int /*<<< orphan*/  assert_refspec (int /*<<< orphan*/ ,char*,int) ; 

void test_network_refspecs__parsing(void)
{
	/* Ported from https://github.com/git/git/blob/abd2bde78bd994166900290434a2048e660dabed/t/t5511-refspec.sh */

	assert_refspec(GIT_DIRECTION_PUSH, "", false);
	assert_refspec(GIT_DIRECTION_PUSH, ":", true);
	assert_refspec(GIT_DIRECTION_PUSH, "::", false);
	assert_refspec(GIT_DIRECTION_PUSH, "+:", true);

	assert_refspec(GIT_DIRECTION_FETCH, "", true);
	assert_refspec(GIT_DIRECTION_PUSH, ":", true);
	assert_refspec(GIT_DIRECTION_FETCH, "::", false);

	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/*:refs/remotes/frotz/*", true);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/*:refs/remotes/frotz", false);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads:refs/remotes/frotz/*", false);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/master:refs/remotes/frotz/xyzzy", true);

	/*
	 * These have invalid LHS, but we do not have a formal "valid sha-1
	 * expression syntax checker" so they are not checked with the current
	 * code.  They will be caught downstream anyway, but we may want to
	 * have tighter check later...
	 */
	/*assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/master::refs/remotes/frotz/xyzzy", false); */
	/*assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/maste :refs/remotes/frotz/xyzzy", false); */

	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/*:refs/remotes/frotz/*", true);
	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/*:refs/remotes/frotz", false);
	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads:refs/remotes/frotz/*", false);
	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/master:refs/remotes/frotz/xyzzy", true);
	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/master::refs/remotes/frotz/xyzzy", false);
	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/maste :refs/remotes/frotz/xyzzy", false);

	assert_refspec(GIT_DIRECTION_PUSH, "master~1:refs/remotes/frotz/backup", true);
	assert_refspec(GIT_DIRECTION_FETCH, "master~1:refs/remotes/frotz/backup", false);
	assert_refspec(GIT_DIRECTION_PUSH, "HEAD~4:refs/remotes/frotz/new", true);
	assert_refspec(GIT_DIRECTION_FETCH, "HEAD~4:refs/remotes/frotz/new", false);

	assert_refspec(GIT_DIRECTION_PUSH, "HEAD", true);
	assert_refspec(GIT_DIRECTION_FETCH, "HEAD", true);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/ nitfol", false);
	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/ nitfol", false);

	assert_refspec(GIT_DIRECTION_PUSH, "HEAD:", false);
	assert_refspec(GIT_DIRECTION_FETCH, "HEAD:", true);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/ nitfol:", false);
	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/ nitfol:", false);

	assert_refspec(GIT_DIRECTION_PUSH, ":refs/remotes/frotz/deleteme", true);
	assert_refspec(GIT_DIRECTION_FETCH, ":refs/remotes/frotz/HEAD-to-me", true);
	assert_refspec(GIT_DIRECTION_PUSH, ":refs/remotes/frotz/delete me", false);
	assert_refspec(GIT_DIRECTION_FETCH, ":refs/remotes/frotz/HEAD to me", false);

	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/*/for-linus:refs/remotes/mine/*-blah", true);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/*/for-linus:refs/remotes/mine/*-blah", true);

	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads*/for-linus:refs/remotes/mine/*", true);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads*/for-linus:refs/remotes/mine/*", true);

	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/*/*/for-linus:refs/remotes/mine/*", false);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/*/*/for-linus:refs/remotes/mine/*", false);

	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/*g*/for-linus:refs/remotes/mine/*", false);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/*g*/for-linus:refs/remotes/mine/*", false);

	assert_refspec(GIT_DIRECTION_FETCH, "refs/heads/*/for-linus:refs/remotes/mine/*", true);
	assert_refspec(GIT_DIRECTION_PUSH, "refs/heads/*/for-linus:refs/remotes/mine/*", true);

	assert_refspec(GIT_DIRECTION_FETCH, "master", true);
	assert_refspec(GIT_DIRECTION_PUSH, "master", true);

	assert_refspec(GIT_DIRECTION_FETCH, "refs/pull/*/head:refs/remotes/origin/pr/*", true);
}