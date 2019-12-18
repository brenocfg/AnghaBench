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
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_filter (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_filter_blob__sanitizes(void)
{
	git_blob *blob;
	git_buf buf;

	cl_git_pass(git_revparse_single(
		(git_object **)&blob, g_repo, "e69de29")); /* zero-byte */

	cl_assert_equal_i(0, git_blob_rawsize(blob));
	cl_assert_equal_s("", git_blob_rawcontent(blob));

	memset(&buf, 0, sizeof(git_buf));
	cl_git_pass(git_blob_filter(&buf, blob, "file.bin", NULL));
	cl_assert_equal_sz(0, buf.size);
	cl_assert_equal_s("", buf.ptr);
	git_buf_dispose(&buf);

	memset(&buf, 0, sizeof(git_buf));
	cl_git_pass(git_blob_filter(&buf, blob, "file.crlf", NULL));
	cl_assert_equal_sz(0, buf.size);
	cl_assert_equal_s("", buf.ptr);
	git_buf_dispose(&buf);

	memset(&buf, 0, sizeof(git_buf));
	cl_git_pass(git_blob_filter(&buf, blob, "file.lf", NULL));
	cl_assert_equal_sz(0, buf.size);
	cl_assert_equal_s("", buf.ptr);
	git_buf_dispose(&buf);

	git_blob_free(blob);
}