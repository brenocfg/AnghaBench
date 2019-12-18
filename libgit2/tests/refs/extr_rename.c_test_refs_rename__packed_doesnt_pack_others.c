#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_rename (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_head_name ; 
 int /*<<< orphan*/  packed_test_head_name ; 
 scalar_t__ reference_is_packed (int /*<<< orphan*/ *) ; 

void test_refs_rename__packed_doesnt_pack_others(void)
{
	/* renaming a packed reference does not pack another reference which happens to be in both loose and pack state */
	git_reference *looked_up_ref, *another_looked_up_ref, *renamed_ref;
	git_buf temp_path = GIT_BUF_INIT;
	const char *brand_new_name = "refs/heads/brand_new_name";

	/* Ensure the other reference exists on the file system */
	cl_git_pass(git_buf_joinpath(&temp_path, git_repository_path(g_repo), packed_test_head_name));
	cl_assert(git_path_exists(temp_path.ptr));

	/* Lookup the other reference */
	cl_git_pass(git_reference_lookup(&another_looked_up_ref, g_repo, packed_test_head_name));

	/* Ensure it's loose */
	cl_assert(reference_is_packed(another_looked_up_ref) == 0);
	git_reference_free(another_looked_up_ref);

	/* Lookup the reference to rename */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, packed_head_name));

	/* Ensure it's packed */
	cl_assert(reference_is_packed(looked_up_ref) != 0);

	/* Now that the reference is renamed... */
	cl_git_pass(git_reference_rename(&renamed_ref, looked_up_ref, brand_new_name, 0, NULL));
	git_reference_free(looked_up_ref);

	/* Lookup the other reference */
	cl_git_pass(git_reference_lookup(&another_looked_up_ref, g_repo, packed_test_head_name));

	/* Ensure it's loose */
	cl_assert(reference_is_packed(another_looked_up_ref) == 0);

	/* Ensure the other ref still exists on the file system */
	cl_assert(git_path_exists(temp_path.ptr));

	git_reference_free(renamed_ref);
	git_reference_free(another_looked_up_ref);
	git_buf_dispose(&temp_path);
}