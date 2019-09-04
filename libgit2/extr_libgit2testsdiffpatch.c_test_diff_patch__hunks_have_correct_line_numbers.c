#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_13__ {int old_lineno; int new_lineno; int content_offset; int /*<<< orphan*/  content_len; int /*<<< orphan*/  content; scalar_t__ origin; } ;
typedef  TYPE_1__ git_diff_line ;
struct TYPE_14__ {scalar_t__ new_lines; scalar_t__ new_start; scalar_t__ old_lines; scalar_t__ old_start; } ;
typedef  TYPE_2__ git_diff_hunk ;
struct TYPE_15__ {scalar_t__ status; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_16__ {char const* ptr; } ;
typedef  TYPE_4__ git_buf ;

/* Variables and functions */
 TYPE_4__ GIT_BUF_INIT ; 
 int GIT_DELTA_MODIFIED ; 
 int GIT_DIFF_LINE_ADDITION ; 
 int GIT_DIFF_LINE_CONTEXT ; 
 int GIT_DIFF_LINE_DELETION ; 
 int GIT_DIFF_LINE_DEL_EOFNL ; 
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_4__*) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_4__*) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* git_patch_get_delta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_get_hunk (TYPE_2__ const**,size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_patch_get_line_in_hunk (TYPE_1__ const**,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ git_patch_num_hunks (int /*<<< orphan*/ *) ; 
 scalar_t__ git_patch_num_lines_in_hunk (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_reinit_filesystem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_repository_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

void test_diff_patch__hunks_have_correct_line_numbers(void)
{
	git_config *cfg;
	git_tree *head;
	git_diff_options opt = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff;
	git_patch *patch;
	const git_diff_delta *delta;
	const git_diff_hunk *hunk;
	const git_diff_line *line;
	size_t hunklen;
	git_buf old_content = GIT_BUF_INIT, actual = GIT_BUF_INIT;
	const char *new_content = "The Song of Seven Cities\n------------------------\n\nI WAS Lord of Cities very sumptuously builded.\nSeven roaring Cities paid me tribute from afar.\nIvory their outposts were--the guardrooms of them gilded,\nAnd garrisoned with Amazons invincible in war.\n\nThis is some new text;\nNot as good as the old text;\nBut here it is.\n\nSo they warred and trafficked only yesterday, my Cities.\nTo-day there is no mark or mound of where my Cities stood.\nFor the River rose at midnight and it washed away my Cities.\nThey are evened with Atlantis and the towns before the Flood.\n\nRain on rain-gorged channels raised the water-levels round them,\nFreshet backed on freshet swelled and swept their world from sight,\nTill the emboldened floods linked arms and, flashing forward, drowned them--\nDrowned my Seven Cities and their peoples in one night!\n\nLow among the alders lie their derelict foundations,\nThe beams wherein they trusted and the plinths whereon they built--\nMy rulers and their treasure and their unborn populations,\nDead, destroyed, aborted, and defiled with mud and silt!\n\nAnother replacement;\nBreaking up the poem;\nGenerating some hunks.\n\nTo the sound of trumpets shall their seed restore my Cities\nWealthy and well-weaponed, that once more may I behold\nAll the world go softly when it walks before my Cities,\nAnd the horses and the chariots fleeing from them as of old!\n\n  -- Rudyard Kipling\n";

	g_repo = cl_git_sandbox_init("renames");

	cl_git_pass(git_config_new(&cfg));
	git_repository_set_config(g_repo, cfg);
	git_config_free(cfg);

	git_repository_reinit_filesystem(g_repo, false);

	cl_git_pass(
		git_futils_readbuffer(&old_content, "renames/songof7cities.txt"));

	cl_git_rewritefile("renames/songof7cities.txt", new_content);

	cl_git_pass(git_repository_head_tree(&head, g_repo));

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, head, &opt));

	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_assert((delta = git_patch_get_delta(patch)) != NULL);

	cl_assert_equal_i(GIT_DELTA_MODIFIED, (int)delta->status);
	cl_assert_equal_i(2, (int)git_patch_num_hunks(patch));

	/* check hunk 0 */

	cl_git_pass(
		git_patch_get_hunk(&hunk, &hunklen, patch, 0));

	cl_assert_equal_i(18, (int)hunklen);

	cl_assert_equal_i(6, (int)hunk->old_start);
	cl_assert_equal_i(15, (int)hunk->old_lines);
	cl_assert_equal_i(6, (int)hunk->new_start);
	cl_assert_equal_i(9, (int)hunk->new_lines);

	cl_assert_equal_i(18, (int)git_patch_num_lines_in_hunk(patch, 0));

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 0));
	cl_assert_equal_i(GIT_DIFF_LINE_CONTEXT, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("Ivory their outposts were--the guardrooms of them gilded,\n", actual.ptr);
	cl_assert_equal_i(6, line->old_lineno);
	cl_assert_equal_i(6, line->new_lineno);
	cl_assert_equal_i(-1, line->content_offset);

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 3));
	cl_assert_equal_i(GIT_DIFF_LINE_DELETION, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("All the world went softly when it walked before my Cities--\n", actual.ptr);
	cl_assert_equal_i(9, line->old_lineno);
	cl_assert_equal_i(-1, line->new_lineno);
	cl_assert_equal_i(252, line->content_offset);

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 12));
	cl_assert_equal_i(GIT_DIFF_LINE_ADDITION, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("This is some new text;\n", actual.ptr);
	cl_assert_equal_i(-1, line->old_lineno);
	cl_assert_equal_i(9, line->new_lineno);
	cl_assert_equal_i(252, line->content_offset);

	/* check hunk 1 */

	cl_git_pass(git_patch_get_hunk(&hunk, &hunklen, patch, 1));

	cl_assert_equal_i(18, (int)hunklen);

	cl_assert_equal_i(31, (int)hunk->old_start);
	cl_assert_equal_i(15, (int)hunk->old_lines);
	cl_assert_equal_i(25, (int)hunk->new_start);
	cl_assert_equal_i(9, (int)hunk->new_lines);

	cl_assert_equal_i(18, (int)git_patch_num_lines_in_hunk(patch, 1));

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 1, 0));
	cl_assert_equal_i(GIT_DIFF_LINE_CONTEXT, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("My rulers and their treasure and their unborn populations,\n", actual.ptr);
	cl_assert_equal_i(31, line->old_lineno);
	cl_assert_equal_i(25, line->new_lineno);
	cl_assert_equal_i(-1, line->content_offset);

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 1, 3));
	cl_assert_equal_i(GIT_DIFF_LINE_DELETION, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("The Daughters of the Palace whom they cherished in my Cities,\n", actual.ptr);
	cl_assert_equal_i(34, line->old_lineno);
	cl_assert_equal_i(-1, line->new_lineno);
	cl_assert_equal_i(1468, line->content_offset);

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 1, 12));
	cl_assert_equal_i(GIT_DIFF_LINE_ADDITION, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("Another replacement;\n", actual.ptr);
	cl_assert_equal_i(-1, line->old_lineno);
	cl_assert_equal_i(28, line->new_lineno);
	cl_assert_equal_i(1066, line->content_offset);

	git_patch_free(patch);
	git_diff_free(diff);

	/* Let's check line numbers when there is no newline */

	git_buf_rtrim(&old_content);
	cl_git_rewritefile("renames/songof7cities.txt", old_content.ptr);

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, head, &opt));

	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_assert((delta = git_patch_get_delta(patch)) != NULL);

	cl_assert_equal_i(GIT_DELTA_MODIFIED, (int)delta->status);
	cl_assert_equal_i(1, (int)git_patch_num_hunks(patch));

	/* check hunk 0 */

	cl_git_pass(git_patch_get_hunk(&hunk, &hunklen, patch, 0));

	cl_assert_equal_i(6, (int)hunklen);

	cl_assert_equal_i(46, (int)hunk->old_start);
	cl_assert_equal_i(4, (int)hunk->old_lines);
	cl_assert_equal_i(46, (int)hunk->new_start);
	cl_assert_equal_i(4, (int)hunk->new_lines);

	cl_assert_equal_i(6, (int)git_patch_num_lines_in_hunk(patch, 0));

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 1));
	cl_assert_equal_i(GIT_DIFF_LINE_CONTEXT, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("And the horses and the chariots fleeing from them as of old!\n", actual.ptr);
	cl_assert_equal_i(47, line->old_lineno);
	cl_assert_equal_i(47, line->new_lineno);

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 2));
	cl_assert_equal_i(GIT_DIFF_LINE_CONTEXT, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("\n", actual.ptr);
	cl_assert_equal_i(48, line->old_lineno);
	cl_assert_equal_i(48, line->new_lineno);

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 3));
	cl_assert_equal_i(GIT_DIFF_LINE_DELETION, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("  -- Rudyard Kipling\n", actual.ptr);
	cl_assert_equal_i(49, line->old_lineno);
	cl_assert_equal_i(-1, line->new_lineno);

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 4));
	cl_assert_equal_i(GIT_DIFF_LINE_ADDITION, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("  -- Rudyard Kipling", actual.ptr);
	cl_assert_equal_i(-1, line->old_lineno);
	cl_assert_equal_i(49, line->new_lineno);

	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 5));
	cl_assert_equal_i(GIT_DIFF_LINE_DEL_EOFNL, (int)line->origin);
	cl_git_pass(git_buf_set(&actual, line->content, line->content_len));
	cl_assert_equal_s("\n\\ No newline at end of file\n", actual.ptr);
	cl_assert_equal_i(-1, line->old_lineno);
	cl_assert_equal_i(49, line->new_lineno);

	git_patch_free(patch);
	git_diff_free(diff);

	git_buf_dispose(&actual);
	git_buf_dispose(&old_content);
	git_tree_free(head);
}