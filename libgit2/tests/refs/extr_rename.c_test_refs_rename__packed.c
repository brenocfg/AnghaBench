#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_reference_rename (TYPE_1__**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 char const* packed_head_name ; 
 scalar_t__ reference_is_packed (TYPE_1__*) ; 

void test_refs_rename__packed(void)
{
	/* rename a packed reference (should make it loose) */
	git_reference *looked_up_ref, *new_ref, *another_looked_up_ref;
	git_buf temp_path = GIT_BUF_INIT;
	const char *brand_new_name = "refs/heads/brand_new_name";

	/* Ensure the ref doesn't exist on the file system */
	cl_git_pass(git_buf_joinpath(&temp_path, git_repository_path(g_repo), packed_head_name));
	cl_assert(!git_path_exists(temp_path.ptr));

	/* The reference can however be looked-up... */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, packed_head_name));

	/* .. and it's packed */
	cl_assert(reference_is_packed(looked_up_ref) != 0);

	/* Now that the reference is renamed... */
	cl_git_pass(git_reference_rename(&new_ref, looked_up_ref, brand_new_name, 0, NULL));
	cl_assert_equal_s(new_ref->name, brand_new_name);
	git_reference_free(looked_up_ref);

	/* ...It can't be looked-up with the old name... */
	cl_git_fail(git_reference_lookup(&another_looked_up_ref, g_repo, packed_head_name));

	/* ...but the new name works ok... */
	cl_git_pass(git_reference_lookup(&another_looked_up_ref, g_repo, brand_new_name));
	cl_assert_equal_s(another_looked_up_ref->name, brand_new_name);

	/* .. the ref is no longer packed... */
	cl_assert(reference_is_packed(another_looked_up_ref) == 0);
	cl_assert(reference_is_packed(new_ref) == 0);

	/* ...and the ref now happily lives in the file system */
	cl_git_pass(git_buf_joinpath(&temp_path, git_repository_path(g_repo), brand_new_name));
	cl_assert(git_path_exists(temp_path.ptr));

	git_reference_free(new_ref);
	git_reference_free(another_looked_up_ref);
	git_buf_dispose(&temp_path);
}