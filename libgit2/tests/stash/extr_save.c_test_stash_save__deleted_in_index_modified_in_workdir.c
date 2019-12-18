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

/* Variables and functions */
 int /*<<< orphan*/  GIT_STASH_DEFAULT ; 
 int GIT_STATUS_INDEX_DELETED ; 
 int GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  assert_blob_oid (char*,char*) ; 
 int /*<<< orphan*/  assert_status (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_save__deleted_in_index_modified_in_workdir(void)
{
	git_index *index;

	git_repository_index(&index, repo);

	cl_git_pass(git_index_remove_bypath(index, "who"));
	cl_git_pass(git_index_write(index));

	assert_status(repo, "who", GIT_STATUS_WT_NEW | GIT_STATUS_INDEX_DELETED);

	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_DEFAULT));

	assert_blob_oid("stash@{0}^0:who", "a0400d4954659306a976567af43125a0b1aa8595");
	assert_blob_oid("stash@{0}^2:who", NULL);

	git_index_free(index);
}