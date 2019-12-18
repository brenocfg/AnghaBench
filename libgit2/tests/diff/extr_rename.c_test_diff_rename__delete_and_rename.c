#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_find_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 char* DELETE_RENAME_COMMIT ; 
 TYPE_2__ GIT_BUF_INIT ; 
 TYPE_1__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_RENAMES_FROM_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 char* RENAME_MODIFICATION_COMMIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_to_buf (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_rename__delete_and_rename(void)
{
	const char *old_sha = RENAME_MODIFICATION_COMMIT;
	const char *new_sha = DELETE_RENAME_COMMIT;
	git_tree *old_tree, *new_tree;
	git_diff *diff;
	git_diff_find_options find_opts = GIT_DIFF_FIND_OPTIONS_INIT;
	git_buf diff_buf = GIT_BUF_INIT;
	const char *expected =
		"diff --git a/sixserving.txt b/sixserving.txt\n"
		"deleted file mode 100644\n"
		"index f90d4fc..0000000\n"
		"--- a/sixserving.txt\n"
		"+++ /dev/null\n"
		"@@ -1,25 +0,0 @@\n"
		"-I  KEEP  six  honest  serving-men\n"
		"-  (They  taught  me  all  I  knew);\n"
		"-Their  names  are  What  and  Why  and  When\n"
		"-  And  How  and  Where  and  Who.\n"
		"-I  send  them  over  land  and  sea,\n"
		"-  I  send  them  east  and  west;\n"
		"-But  after  they  have  worked  for  me,\n"
		"-  I  give  them  all  a  rest.\n"
		"-\n"
		"-I  let  them  rest  from  nine  till  five,\n"
		"-  For  I  am  busy  then,\n"
		"-As  well  as  breakfast,  lunch,  and  tea,\n"
		"-  For  they  are  hungry  men.\n"
		"-But  different  folk  have  different  views;\n"
		"-I  know  a  person  small—\n"
		"-She  keeps  ten  million  serving-men,\n"
		"-Who  get  no  rest  at  all!\n"
		"-\n"
		"-She  sends'em  abroad  on  her  own  affairs,\n"
		"-  From  the  second  she  opens  her  eyes—\n"
		"-One  million  Hows,  two  million  Wheres,\n"
		"-And  seven  million  Whys!\n"
		"-\n"
		"-    --  Rudyard  Kipling\n"
		"-\n"
		"diff --git a/songof7cities.txt b/sixserving.txt\n"
		"similarity index 100%\n"
		"rename from songof7cities.txt\n"
		"rename to sixserving.txt\n";

	old_tree = resolve_commit_oid_to_tree(g_repo, old_sha);
	new_tree = resolve_commit_oid_to_tree(g_repo, new_sha);

	find_opts.flags = GIT_DIFF_FIND_RENAMES_FROM_REWRITES;

	cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, old_tree, new_tree, NULL));
	cl_git_pass(git_diff_find_similar(diff, &find_opts));

	cl_git_pass(git_diff_to_buf(&diff_buf, diff, GIT_DIFF_FORMAT_PATCH));

	cl_assert_equal_s(expected, diff_buf.ptr);

	git_buf_dispose(&diff_buf);
	git_diff_free(diff);
	git_tree_free(old_tree);
	git_tree_free(new_tree);
}