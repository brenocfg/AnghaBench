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
 int /*<<< orphan*/  GIT_STASH_DEFAULT ; 
 int /*<<< orphan*/  GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  assert_blob_oid (char*,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_save__does_not_keep_index_by_default(void)
{
/*
$ git stash

$ git show refs/stash:what
see you later

$ git show refs/stash:how
not so small and

$ git show refs/stash:who
funky world

$ git show refs/stash:when
fatal: Path 'when' exists on disk, but not in 'stash'.

$ git show refs/stash^2:what
goodbye

$ git show refs/stash^2:how
not so small and

$ git show refs/stash^2:who
world

$ git show refs/stash^2:when
fatal: Path 'when' exists on disk, but not in 'stash^2'.

$ git status --short
?? when

*/
	unsigned int status;

	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_DEFAULT));
	cl_git_pass(git_status_file(&status, repo, "when"));

	assert_blob_oid("refs/stash:what", "bc99dc98b3eba0e9157e94769cd4d49cb49de449");	/* see you later */
	assert_blob_oid("refs/stash:how", "e6d64adb2c7f3eb8feb493b556cc8070dca379a3");	/* not so small and */
	assert_blob_oid("refs/stash:who", "a0400d4954659306a976567af43125a0b1aa8595");	/* funky world */
	assert_blob_oid("refs/stash:when", NULL);
	assert_blob_oid("refs/stash:why", "88c2533e21f098b89c91a431d8075cbdbe422a51"); /* would anybody use stash? */
	assert_blob_oid("refs/stash:where", "e3d6434ec12eb76af8dfa843a64ba6ab91014a0b"); /* .... */
	assert_blob_oid("refs/stash:.gitignore", "ac4d88de61733173d9959e4b77c69b9f17a00980");
	assert_blob_oid("refs/stash:just.ignore", NULL);

	assert_blob_oid("refs/stash^2:what", "dd7e1c6f0fefe118f0b63d9f10908c460aa317a6");	/* goodbye */
	assert_blob_oid("refs/stash^2:how", "e6d64adb2c7f3eb8feb493b556cc8070dca379a3");	/* not so small and */
	assert_blob_oid("refs/stash^2:who", "cc628ccd10742baea8241c5924df992b5c019f71");	/* world */
	assert_blob_oid("refs/stash^2:when", NULL);
	assert_blob_oid("refs/stash^2:why", "88c2533e21f098b89c91a431d8075cbdbe422a51"); /* would anybody use stash? */
	assert_blob_oid("refs/stash^2:where", "e08f7fbb9a42a0c5367cf8b349f1f08c3d56bd72"); /* ???? */
	assert_blob_oid("refs/stash^2:.gitignore", "ac4d88de61733173d9959e4b77c69b9f17a00980");
	assert_blob_oid("refs/stash^2:just.ignore", NULL);

	assert_blob_oid("refs/stash^3", NULL);

	cl_assert_equal_i(GIT_STATUS_WT_NEW, status);
}