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
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_STASH_DEFAULT ; 
 int /*<<< orphan*/  GIT_STASH_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_CURRENT ; 
 int GIT_STATUS_IGNORED ; 
 int GIT_STATUS_INDEX_MODIFIED ; 
 int GIT_STATUS_WT_MODIFIED ; 
 int GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  assert_blob_oid (char*,char*) ; 
 int /*<<< orphan*/  assert_object_oid (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_status (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_save__can_stage_normal_then_stage_untracked(void)
{
	/*
	 * $ git ls-tree stash@{1}^0
	 * 100644 blob ac4d88de61733173d9959e4b77c69b9f17a00980    .gitignore
	 * 100644 blob e6d64adb2c7f3eb8feb493b556cc8070dca379a3    how
	 * 100644 blob bc99dc98b3eba0e9157e94769cd4d49cb49de449    what
	 * 100644 blob a0400d4954659306a976567af43125a0b1aa8595    who
	 *
	 * $ git ls-tree stash@{1}^1
	 * 100644 blob ac4d88de61733173d9959e4b77c69b9f17a00980    .gitignore
	 * 100644 blob ac790413e2d7a26c3767e78c57bb28716686eebc    how
	 * 100644 blob ce013625030ba8dba906f756967f9e9ca394464a    what
	 * 100644 blob cc628ccd10742baea8241c5924df992b5c019f71    who
	 *
	 * $ git ls-tree stash@{1}^2
	 * 100644 blob ac4d88de61733173d9959e4b77c69b9f17a00980    .gitignore
	 * 100644 blob e6d64adb2c7f3eb8feb493b556cc8070dca379a3    how
	 * 100644 blob dd7e1c6f0fefe118f0b63d9f10908c460aa317a6    what
	 * 100644 blob cc628ccd10742baea8241c5924df992b5c019f71    who
	 *
	 * $ git ls-tree stash@{1}^3
	 * fatal: Not a valid object name stash@{1}^3
	 *
	 * $ git ls-tree stash@{0}^0
	 * 100644 blob ac4d88de61733173d9959e4b77c69b9f17a00980    .gitignore
	 * 100644 blob ac790413e2d7a26c3767e78c57bb28716686eebc    how
	 * 100644 blob ce013625030ba8dba906f756967f9e9ca394464a    what
	 * 100644 blob cc628ccd10742baea8241c5924df992b5c019f71    who
	 *
	 * $ git ls-tree stash@{0}^1
	 * 100644 blob ac4d88de61733173d9959e4b77c69b9f17a00980    .gitignore
	 * 100644 blob ac790413e2d7a26c3767e78c57bb28716686eebc    how
	 * 100644 blob ce013625030ba8dba906f756967f9e9ca394464a    what
	 * 100644 blob cc628ccd10742baea8241c5924df992b5c019f71    who
	 *
	 * $ git ls-tree stash@{0}^2
	 * 100644 blob ac4d88de61733173d9959e4b77c69b9f17a00980    .gitignore
	 * 100644 blob ac790413e2d7a26c3767e78c57bb28716686eebc    how
	 * 100644 blob ce013625030ba8dba906f756967f9e9ca394464a    what
	 * 100644 blob cc628ccd10742baea8241c5924df992b5c019f71    who
	 *
	 * $ git ls-tree stash@{0}^3
	 * 100644 blob b6ed15e81e2593d7bb6265eb4a991d29dc3e628b    when
	*/

	assert_status(repo, "what", GIT_STATUS_WT_MODIFIED | GIT_STATUS_INDEX_MODIFIED);
	assert_status(repo, "how", GIT_STATUS_INDEX_MODIFIED);
	assert_status(repo, "who", GIT_STATUS_WT_MODIFIED);
	assert_status(repo, "when", GIT_STATUS_WT_NEW);
	assert_status(repo, "just.ignore", GIT_STATUS_IGNORED);

	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_DEFAULT));
	assert_status(repo, "what", GIT_STATUS_CURRENT);
	assert_status(repo, "how", GIT_STATUS_CURRENT);
	assert_status(repo, "who", GIT_STATUS_CURRENT);
	assert_status(repo, "when", GIT_STATUS_WT_NEW);
	assert_status(repo, "just.ignore", GIT_STATUS_IGNORED);

	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_INCLUDE_UNTRACKED));
	assert_status(repo, "what", GIT_STATUS_CURRENT);
	assert_status(repo, "how", GIT_STATUS_CURRENT);
	assert_status(repo, "who", GIT_STATUS_CURRENT);
	assert_status(repo, "when", GIT_ENOTFOUND);
	assert_status(repo, "just.ignore", GIT_STATUS_IGNORED);


	assert_blob_oid("stash@{1}^0:what", "bc99dc98b3eba0e9157e94769cd4d49cb49de449");	/* see you later */
	assert_blob_oid("stash@{1}^0:how", "e6d64adb2c7f3eb8feb493b556cc8070dca379a3");		/* not so small and */
	assert_blob_oid("stash@{1}^0:who", "a0400d4954659306a976567af43125a0b1aa8595");		/* funky world */
	assert_blob_oid("stash@{1}^0:when", NULL);

	assert_blob_oid("stash@{1}^2:what", "dd7e1c6f0fefe118f0b63d9f10908c460aa317a6");	/* goodbye */
	assert_blob_oid("stash@{1}^2:how", "e6d64adb2c7f3eb8feb493b556cc8070dca379a3");		/* not so small and */
	assert_blob_oid("stash@{1}^2:who", "cc628ccd10742baea8241c5924df992b5c019f71");		/* world */
	assert_blob_oid("stash@{1}^2:when", NULL);

	assert_object_oid("stash@{1}^3", NULL, GIT_OBJECT_COMMIT);

	assert_blob_oid("stash@{0}^0:what", "ce013625030ba8dba906f756967f9e9ca394464a");	/* hello */
	assert_blob_oid("stash@{0}^0:how", "ac790413e2d7a26c3767e78c57bb28716686eebc");		/* small */
	assert_blob_oid("stash@{0}^0:who", "cc628ccd10742baea8241c5924df992b5c019f71");		/* world */
	assert_blob_oid("stash@{0}^0:when", NULL);

	assert_blob_oid("stash@{0}^2:what", "ce013625030ba8dba906f756967f9e9ca394464a");	/* hello */
	assert_blob_oid("stash@{0}^2:how", "ac790413e2d7a26c3767e78c57bb28716686eebc");		/* small */
	assert_blob_oid("stash@{0}^2:who", "cc628ccd10742baea8241c5924df992b5c019f71");		/* world */
	assert_blob_oid("stash@{0}^2:when", NULL);

	assert_blob_oid("stash@{0}^3:when", "b6ed15e81e2593d7bb6265eb4a991d29dc3e628b");	/* now */
}