#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** oids; scalar_t__ invokes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_STASH_DEFAULT ; 
 int /*<<< orphan*/  GIT_STASH_INCLUDE_IGNORED ; 
 int /*<<< orphan*/  GIT_STASH_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  REPO_NAME ; 
 int /*<<< orphan*/  callback_cb ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,scalar_t__) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ data ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  setup_stash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_foreach__can_enumerate_a_repository(void)
{
	char *oids_default[] = {
		"493568b7a2681187aaac8a58d3f1eab1527cba84", NULL };

	char *oids_untracked[] = {
		"7f89a8b15c878809c5c54d1ff8f8c9674154017b",
		"493568b7a2681187aaac8a58d3f1eab1527cba84", NULL };

	char *oids_ignored[] = {
		"c95599a8fef20a7e57582c6727b1a0d02e0a5828",
		"7f89a8b15c878809c5c54d1ff8f8c9674154017b",
		"493568b7a2681187aaac8a58d3f1eab1527cba84", NULL };

	cl_git_pass(git_repository_init(&repo, REPO_NAME, 0));

	setup_stash(repo, signature);

	cl_git_pass(git_stash_save(
		&stash_tip_oid,
		repo,
		signature,
		NULL,
		GIT_STASH_DEFAULT));

	data.oids = oids_default;

	cl_git_pass(git_stash_foreach(repo, callback_cb, &data));
	cl_assert_equal_i(1, data.invokes);

	/* ensure stash_foreach operates with INCLUDE_UNTRACKED */
	cl_git_pass(git_stash_save(
		&stash_tip_oid,
		repo,
		signature,
		NULL,
		GIT_STASH_INCLUDE_UNTRACKED));

	data.oids = oids_untracked;
	data.invokes = 0;

	cl_git_pass(git_stash_foreach(repo, callback_cb, &data));
	cl_assert_equal_i(2, data.invokes);

	/* ensure stash_foreach operates with INCLUDE_IGNORED */
	cl_git_pass(git_stash_save(
		&stash_tip_oid,
		repo,
		signature,
		NULL,
		GIT_STASH_INCLUDE_IGNORED));

	data.oids = oids_ignored;
	data.invokes = 0;

	cl_git_pass(git_stash_foreach(repo, callback_cb, &data));
	cl_assert_equal_i(3, data.invokes);
}