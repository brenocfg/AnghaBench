#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_blob ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_filter (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_filter_custom__order_dependency(void)
{
	git_index *index;
	git_blob *blob;
	git_buf buf = { 0 };

	/* so if ident and reverse are used together, an interesting thing
	 * happens - a reversed "$Id$" string is no longer going to trigger
	 * ident correctly.  When checking out, the filters should be applied
	 * in order CLRF, then ident, then reverse, so ident expansion should
	 * work correctly.  On check in, the content should be reversed, then
	 * ident, then CRLF filtered.  Let's make sure that works...
	 */

	cl_git_mkfile(
		"empty_standard_repo/.gitattributes",
		"hero.*.rev-ident text ident prereverse eol=lf\n");

	cl_git_mkfile(
		"empty_standard_repo/hero.1.rev-ident",
		"This is a test\n$Id$\nHave fun!\n");

	cl_git_mkfile(
		"empty_standard_repo/hero.2.rev-ident",
		"Another test\n$dI$\nCrazy!\n");

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_add_bypath(index, "hero.1.rev-ident"));
	cl_git_pass(git_index_add_bypath(index, "hero.2.rev-ident"));
	cl_repo_commit_from_index(NULL, g_repo, NULL, 0, "Filter chains\n");
	git_index_free(index);

	cl_git_pass(git_blob_lookup(&blob, g_repo,
		& git_index_get_bypath(index, "hero.1.rev-ident", 0)->id));
	cl_assert_equal_s(
		"\n!nuf evaH\n$dI$\ntset a si sihT", git_blob_rawcontent(blob));
	cl_git_pass(git_blob_filter(&buf, blob, "hero.1.rev-ident", NULL));
	/* no expansion because id was reversed at checkin and now at ident
	 * time, reverse is not applied yet */
	cl_assert_equal_s(
		"This is a test\n$Id$\nHave fun!\n", buf.ptr);
	git_blob_free(blob);

	cl_git_pass(git_blob_lookup(&blob, g_repo,
		& git_index_get_bypath(index, "hero.2.rev-ident", 0)->id));
	cl_assert_equal_s(
		"\n!yzarC\n$Id$\ntset rehtonA", git_blob_rawcontent(blob));
	cl_git_pass(git_blob_filter(&buf, blob, "hero.2.rev-ident", NULL));
	/* expansion because reverse was applied at checkin and at ident time,
	 * reverse is not applied yet */
	cl_assert_equal_s(
		"Another test\n$ 59001fe193103b1016b27027c0c827d036fd0ac8 :dI$\nCrazy!\n", buf.ptr);
	cl_assert_equal_i(0, git_oid_strcmp(
		git_blob_id(blob), "8ca0df630d728c0c72072b6101b301391ef10095"));
	git_blob_free(blob);

	git_buf_dispose(&buf);
}