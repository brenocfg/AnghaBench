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
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CRLF_TEXT_AS_CRLF ; 
 int /*<<< orphan*/  ALL_CRLF_TEXT_RAW ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_filter (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_filter_bare__all_crlf(void)
{
	git_blob *blob;
	git_buf buf = { 0 };

	cl_git_pass(git_revparse_single(
		(git_object **)&blob, g_repo, "a9a2e89")); /* all-crlf */

	cl_assert_equal_s(ALL_CRLF_TEXT_RAW, git_blob_rawcontent(blob));

	cl_git_pass(git_blob_filter(&buf, blob, "file.bin", &filter_opts));

	cl_assert_equal_s(ALL_CRLF_TEXT_RAW, buf.ptr);

	cl_git_pass(git_blob_filter(&buf, blob, "file.crlf", &filter_opts));

	/* in this case, raw content has crlf in it already */
	cl_assert_equal_s(ALL_CRLF_TEXT_AS_CRLF, buf.ptr);

	cl_git_pass(git_blob_filter(&buf, blob, "file.lf", &filter_opts));

	/* we never convert CRLF -> LF on platforms that have LF */
	cl_assert_equal_s(ALL_CRLF_TEXT_AS_CRLF, buf.ptr);

	cl_git_pass(git_blob_filter(&buf, blob, "file.txt", &filter_opts));

	/* in this case, raw content has crlf in it already */
	cl_assert_equal_s(ALL_CRLF_TEXT_AS_CRLF, buf.ptr);

	git_buf_dispose(&buf);
	git_blob_free(blob);
}