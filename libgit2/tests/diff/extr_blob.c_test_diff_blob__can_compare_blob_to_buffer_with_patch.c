#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_blob ;
struct TYPE_5__ {int status; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int GIT_DELTA_ADDED ; 
 int GIT_DELTA_DELETED ; 
 int GIT_DELTA_MODIFIED ; 
 int GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_REVERSE ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_oid_fromstrn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_blob_and_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* git_patch_get_delta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_line_stats (size_t*,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_patch_num_hunks (int /*<<< orphan*/ *) ; 
 int git_patch_num_lines_in_hunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ opts ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_blob__can_compare_blob_to_buffer_with_patch(void)
{
	git_patch *p;
	git_blob *a;
	git_oid a_oid;
	const char *a_content = "Hello from the root\n";
	const char *b_content = "Hello from the root\n\nSome additional lines\n\nDown here below\n\n";
	size_t tc, ta, td;

	/* tests/resources/attr/root_test1 */
	cl_git_pass(git_oid_fromstrn(&a_oid, "45141a79", 8));
	cl_git_pass(git_blob_lookup_prefix(&a, g_repo, &a_oid, 8));

	/* diff from blob a to content of b */
	cl_git_pass(git_patch_from_blob_and_buffer(
		&p, a, NULL, b_content, strlen(b_content), NULL, &opts));

	cl_assert(p != NULL);
	cl_assert_equal_i(GIT_DELTA_MODIFIED, git_patch_get_delta(p)->status);
	cl_assert_equal_i(1, (int)git_patch_num_hunks(p));
	cl_assert_equal_i(6, git_patch_num_lines_in_hunk(p, 0));

	cl_git_pass(git_patch_line_stats(&tc, &ta, &td, p));
	cl_assert_equal_i(1, (int)tc);
	cl_assert_equal_i(5, (int)ta);
	cl_assert_equal_i(0, (int)td);

	git_patch_free(p);

	/* diff from blob a to content of a */
	opts.flags |= GIT_DIFF_INCLUDE_UNMODIFIED;
	cl_git_pass(git_patch_from_blob_and_buffer(
		&p, a, NULL, a_content, strlen(a_content), NULL, &opts));
	cl_assert(p != NULL);
	cl_assert_equal_i(GIT_DELTA_UNMODIFIED, git_patch_get_delta(p)->status);
	cl_assert_equal_i(0, (int)git_patch_num_hunks(p));
	git_patch_free(p);

	/* diff from NULL blob to content of a */
	cl_git_pass(git_patch_from_blob_and_buffer(
		&p, NULL, NULL, a_content, strlen(a_content), NULL, &opts));
	cl_assert(p != NULL);
	cl_assert_equal_i(GIT_DELTA_ADDED, git_patch_get_delta(p)->status);
	cl_assert_equal_i(1, (int)git_patch_num_hunks(p));
	cl_assert_equal_i(1, git_patch_num_lines_in_hunk(p, 0));
	git_patch_free(p);

	/* diff from blob a to NULL buffer */
	cl_git_pass(git_patch_from_blob_and_buffer(
		&p, a, NULL, NULL, 0, NULL, &opts));
	cl_assert(p != NULL);
	cl_assert_equal_i(GIT_DELTA_DELETED, git_patch_get_delta(p)->status);
	cl_assert_equal_i(1, (int)git_patch_num_hunks(p));
	cl_assert_equal_i(1, git_patch_num_lines_in_hunk(p, 0));
	git_patch_free(p);

	/* diff with reverse */
	opts.flags ^= GIT_DIFF_REVERSE;

	cl_git_pass(git_patch_from_blob_and_buffer(
		&p, a, NULL, NULL, 0, NULL, &opts));
	cl_assert(p != NULL);
	cl_assert_equal_i(GIT_DELTA_ADDED, git_patch_get_delta(p)->status);
	cl_assert_equal_i(1, (int)git_patch_num_hunks(p));
	cl_assert_equal_i(1, git_patch_num_lines_in_hunk(p, 0));
	git_patch_free(p);

	git_blob_free(a);
}