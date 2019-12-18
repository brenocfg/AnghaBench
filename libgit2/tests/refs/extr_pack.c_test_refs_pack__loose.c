#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_PACKEDREFS_FILE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loose_tag_ref_name ; 
 int /*<<< orphan*/  packall () ; 
 int reference_is_packed (TYPE_1__*) ; 

void test_refs_pack__loose(void)
{
	/* create a packfile from all the loose refs in a repo */
	git_reference *reference;
	git_buf temp_path = GIT_BUF_INIT;

	/* Ensure a known loose ref can be looked up */
	cl_git_pass(git_reference_lookup(&reference, g_repo, loose_tag_ref_name));
	cl_assert(reference_is_packed(reference) == 0);
	cl_assert_equal_s(reference->name, loose_tag_ref_name);
	git_reference_free(reference);

	/*
	 * We are now trying to pack also a loose reference
	 * called `points_to_blob`, to make sure we can properly
	 * pack weak tags
	 */
	packall();

	/* Ensure the packed-refs file exists */
	cl_git_pass(git_buf_joinpath(&temp_path, git_repository_path(g_repo), GIT_PACKEDREFS_FILE));
	cl_assert(git_path_exists(temp_path.ptr));

	/* Ensure the known ref can still be looked up but is now packed */
	cl_git_pass(git_reference_lookup(&reference, g_repo, loose_tag_ref_name));
	cl_assert(reference_is_packed(reference));
	cl_assert_equal_s(reference->name, loose_tag_ref_name);

	/* Ensure the known ref has been removed from the loose folder structure */
	cl_git_pass(git_buf_joinpath(&temp_path, git_repository_path(g_repo), loose_tag_ref_name));
	cl_assert(!git_path_exists(temp_path.ptr));

	git_reference_free(reference);
	git_buf_dispose(&temp_path);
}