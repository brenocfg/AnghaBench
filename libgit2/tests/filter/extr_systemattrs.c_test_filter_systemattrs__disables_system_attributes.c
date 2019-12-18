#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ git_blob_filter_options ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_LF_TEXT_RAW ; 
 int /*<<< orphan*/  GIT_BLOB_FILTER_NO_SYSTEM_ATTRIBUTES ; 
 TYPE_2__ GIT_BLOB_FILTER_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_filter (TYPE_1__*,int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_filter_systemattrs__disables_system_attributes(void)
{
	git_blob *blob;
	git_buf buf = { 0 };
	git_blob_filter_options opts = GIT_BLOB_FILTER_OPTIONS_INIT;

	opts.flags |= GIT_BLOB_FILTER_NO_SYSTEM_ATTRIBUTES;

	cl_git_pass(git_revparse_single(
		(git_object **)&blob, g_repo, "799770d")); /* all-lf */

	cl_assert_equal_s(ALL_LF_TEXT_RAW, git_blob_rawcontent(blob));

	cl_git_pass(git_blob_filter(&buf, blob, "file.bin", &opts));
	cl_assert_equal_s(ALL_LF_TEXT_RAW, buf.ptr);

	/* No attributes mean these are all treated literally */
	cl_git_pass(git_blob_filter(&buf, blob, "file.crlf", &opts));
	cl_assert_equal_s(ALL_LF_TEXT_RAW, buf.ptr);

	cl_git_pass(git_blob_filter(&buf, blob, "file.lf", &opts));
	cl_assert_equal_s(ALL_LF_TEXT_RAW, buf.ptr);

	git_buf_dispose(&buf);
	git_blob_free(blob);
}