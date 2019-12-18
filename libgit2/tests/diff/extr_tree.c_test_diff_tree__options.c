#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_4__ {int member_0; int member_3; int member_6; int member_7; int member_8; int member_9; scalar_t__ files; scalar_t__* file_status; scalar_t__ hunks; scalar_t__ lines; scalar_t__ line_ctxt; scalar_t__ line_adds; scalar_t__ line_dels; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ diff_expects ;
typedef  int /*<<< orphan*/  actual ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_OPTS (int,int) ; 
 int /*<<< orphan*/  EXPECT_STATUS_ADM (int,int,int) ; 
 int GIT_DELTA_TYPECHANGE ; 
 int GIT_DELTA_UNMODIFIED ; 
 int GIT_DIFF_FORCE_TEXT ; 
 int GIT_DIFF_IGNORE_WHITESPACE ; 
 int GIT_DIFF_IGNORE_WHITESPACE_CHANGE ; 
 int GIT_DIFF_IGNORE_WHITESPACE_EOL ; 
 int GIT_DIFF_NORMAL ; 
 int GIT_DIFF_REVERSE ; 
 int /*<<< orphan*/ * a ; 
 int /*<<< orphan*/ * b ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/ * diff ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opts ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_tree__options(void)
{
	/* grabbed a couple of commit oids from the history of the attr repo */
	const char *a_commit = "6bab5c79cd5140d0";
	const char *b_commit = "605812ab7fe421fdd";
	const char *c_commit = "f5b0af1fb4f5";
	const char *d_commit = "a97cc019851";
	git_tree *c, *d;
	diff_expects actual;
	int test_ab_or_cd[] = { 0, 0, 0, 0, 1, 1, 1, 1, 1 };
	git_diff_options test_options[] = {
		/* a vs b tests */
		DIFF_OPTS(GIT_DIFF_NORMAL, 1),
		DIFF_OPTS(GIT_DIFF_NORMAL, 3),
		DIFF_OPTS(GIT_DIFF_REVERSE, 2),
		DIFF_OPTS(GIT_DIFF_FORCE_TEXT, 2),
		/* c vs d tests */
		DIFF_OPTS(GIT_DIFF_NORMAL, 3),
		DIFF_OPTS(GIT_DIFF_IGNORE_WHITESPACE, 3),
		DIFF_OPTS(GIT_DIFF_IGNORE_WHITESPACE_CHANGE, 3),
		DIFF_OPTS(GIT_DIFF_IGNORE_WHITESPACE_EOL, 3),
		DIFF_OPTS(GIT_DIFF_IGNORE_WHITESPACE | GIT_DIFF_REVERSE, 1),
	};

	/* to generate these values:
	 * - cd to tests/resources/attr,
	 * - mv .gitted .git
	 * - git diff [options] 6bab5c79cd5140d0 605812ab7fe421fdd
	 * - mv .git .gitted
	 */
#define EXPECT_STATUS_ADM(ADDS,DELS,MODS) { 0, ADDS, DELS, MODS, 0, 0, 0, 0, 0 }

	diff_expects test_expects[] = {
		/* a vs b tests */
		{ 5, 0, EXPECT_STATUS_ADM(3, 0, 2), 4, 0, 0, 51, 2, 46, 3 },
		{ 5, 0, EXPECT_STATUS_ADM(3, 0, 2), 4, 0, 0, 53, 4, 46, 3 },
		{ 5, 0, EXPECT_STATUS_ADM(0, 3, 2), 4, 0, 0, 52, 3, 3, 46 },
		{ 5, 0, EXPECT_STATUS_ADM(3, 0, 2), 5, 0, 0, 54, 3, 47, 4 },
		/* c vs d tests */
		{ 1, 0, EXPECT_STATUS_ADM(0, 0, 1), 1, 0, 0, 22, 9, 10, 3 },
		{ 1, 0, EXPECT_STATUS_ADM(0, 0, 1), 1, 0, 0, 19, 12, 7, 0 },
		{ 1, 0, EXPECT_STATUS_ADM(0, 0, 1), 1, 0, 0, 20, 11, 8, 1 },
		{ 1, 0, EXPECT_STATUS_ADM(0, 0, 1), 1, 0, 0, 20, 11, 8, 1 },
		{ 1, 0, EXPECT_STATUS_ADM(0, 0, 1), 1, 0, 0, 18, 11, 0, 7 },
		{ 0 },
	};
	diff_expects *expected;
	int i, j;

	g_repo = cl_git_sandbox_init("attr");

	cl_assert((a = resolve_commit_oid_to_tree(g_repo, a_commit)) != NULL);
	cl_assert((b = resolve_commit_oid_to_tree(g_repo, b_commit)) != NULL);
	cl_assert((c = resolve_commit_oid_to_tree(g_repo, c_commit)) != NULL);
	cl_assert((d = resolve_commit_oid_to_tree(g_repo, d_commit)) != NULL);

	for (i = 0; test_expects[i].files > 0; i++) {
		memset(&actual, 0, sizeof(actual)); /* clear accumulator */
		opts = test_options[i];

		if (test_ab_or_cd[i] == 0)
			cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, a, b, &opts));
		else
			cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, c, d, &opts));

		cl_git_pass(git_diff_foreach(
			diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &actual));

		expected = &test_expects[i];
		cl_assert_equal_i(actual.files,     expected->files);
		for (j = GIT_DELTA_UNMODIFIED; j <= GIT_DELTA_TYPECHANGE; ++j)
			cl_assert_equal_i(expected->file_status[j], actual.file_status[j]);
		cl_assert_equal_i(actual.hunks,     expected->hunks);
		cl_assert_equal_i(actual.lines,     expected->lines);
		cl_assert_equal_i(actual.line_ctxt, expected->line_ctxt);
		cl_assert_equal_i(actual.line_adds, expected->line_adds);
		cl_assert_equal_i(actual.line_dels, expected->line_dels);

		git_diff_free(diff);
		diff = NULL;
	}

	git_tree_free(c);
	git_tree_free(d);
}