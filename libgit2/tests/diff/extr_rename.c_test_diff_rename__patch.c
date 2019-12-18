#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
struct TYPE_15__ {int flags; } ;
typedef  TYPE_2__ git_diff_find_options ;
struct TYPE_16__ {scalar_t__ status; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_17__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ git_buf ;

/* Variables and functions */
 char* COPY_RENAME_COMMIT ; 
 TYPE_4__ GIT_BUF_INIT ; 
 int GIT_DELTA_COPIED ; 
 int GIT_DELTA_MODIFIED ; 
 int GIT_DELTA_UNMODIFIED ; 
 int GIT_DIFF_FIND_COPIES ; 
 TYPE_2__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int GIT_DIFF_FIND_RENAMES ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNMODIFIED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 char* REWRITE_COPY_COMMIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_4__*) ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_3__* git_diff_get_delta (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* git_patch_get_delta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_rename__patch(void)
{
	const char *sha0 = COPY_RENAME_COMMIT;
	const char *sha1 = REWRITE_COPY_COMMIT;
	git_tree *old_tree, *new_tree;
	git_diff *diff;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options opts = GIT_DIFF_FIND_OPTIONS_INIT;
	git_patch *patch;
	const git_diff_delta *delta;
	git_buf buf = GIT_BUF_INIT;
	const char *expected = "diff --git a/sixserving.txt b/ikeepsix.txt\nindex ad0a8e5..36020db 100644\n--- a/sixserving.txt\n+++ b/ikeepsix.txt\n@@ -1,3 +1,6 @@\n+I Keep Six Honest Serving-Men\n+=============================\n+\n I KEEP six honest serving-men\n  (They taught me all I knew);\n Their names are What and Why and When\n@@ -21,4 +24,4 @@ She sends'em abroad on her own affairs,\n One million Hows, two million Wheres,\n And seven million Whys!\n \n-                -- Rudyard Kipling\n+  -- Rudyard Kipling\n";

	old_tree = resolve_commit_oid_to_tree(g_repo, sha0);
	new_tree = resolve_commit_oid_to_tree(g_repo, sha1);

	diffopts.flags |= GIT_DIFF_INCLUDE_UNMODIFIED;
	cl_git_pass(git_diff_tree_to_tree(
		&diff, g_repo, old_tree, new_tree, &diffopts));

	opts.flags = GIT_DIFF_FIND_RENAMES | GIT_DIFF_FIND_COPIES;
	cl_git_pass(git_diff_find_similar(diff, &opts));

	/* == Changes =====================================================
	 * sixserving.txt  -> ikeepsix.txt    (copy, add title, >80% match)
	 * sevencities.txt                    (no change)
	 * sixserving.txt  -> sixserving.txt  (indentation change)
	 * songofseven.txt -> songofseven.txt (major rewrite, <20% match - split)
	 */

	cl_assert_equal_i(4, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_assert((delta = git_patch_get_delta(patch)) != NULL);
	cl_assert_equal_i(GIT_DELTA_COPIED, (int)delta->status);

	cl_git_pass(git_patch_to_buf(&buf, patch));
	cl_assert_equal_s(expected, buf.ptr);
	git_buf_dispose(&buf);

	git_patch_free(patch);

	cl_assert((delta = git_diff_get_delta(diff, 1)) != NULL);
	cl_assert_equal_i(GIT_DELTA_UNMODIFIED, (int)delta->status);

	cl_assert((delta = git_diff_get_delta(diff, 2)) != NULL);
	cl_assert_equal_i(GIT_DELTA_MODIFIED, (int)delta->status);

	cl_assert((delta = git_diff_get_delta(diff, 3)) != NULL);
	cl_assert_equal_i(GIT_DELTA_MODIFIED, (int)delta->status);

	git_diff_free(diff);
	git_tree_free(old_tree);
	git_tree_free(new_tree);
}