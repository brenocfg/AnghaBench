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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_create_from_workdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_blob_filter (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 

void test_filter_blob__ident(void)
{
	git_oid id;
	git_blob *blob;
	git_buf buf = { 0 };

	cl_git_mkfile("crlf/test.ident", "Some text\n$Id$\nGoes there\n");
	cl_git_pass(git_blob_create_from_workdir(&id, g_repo, "test.ident"));
	cl_git_pass(git_blob_lookup(&blob, g_repo, &id));
	cl_assert_equal_s(
		"Some text\n$Id$\nGoes there\n", git_blob_rawcontent(blob));
	git_blob_free(blob);

	cl_git_mkfile("crlf/test.ident", "Some text\n$Id: Any old just you want$\nGoes there\n");
	cl_git_pass(git_blob_create_from_workdir(&id, g_repo, "test.ident"));
	cl_git_pass(git_blob_lookup(&blob, g_repo, &id));
	cl_assert_equal_s(
		"Some text\n$Id$\nGoes there\n", git_blob_rawcontent(blob));

	cl_git_pass(git_blob_filter(&buf, blob, "filter.bin", NULL));
	cl_assert_equal_s(
		"Some text\n$Id$\nGoes there\n", buf.ptr);

	cl_git_pass(git_blob_filter(&buf, blob, "filter.identcrlf", NULL));
	cl_assert_equal_s(
		"Some text\r\n$Id: 3164f585d548ac68027d22b104f2d8100b2b6845 $\r\nGoes there\r\n", buf.ptr);

	cl_git_pass(git_blob_filter(&buf, blob, "filter.identlf", NULL));
	cl_assert_equal_s(
		"Some text\n$Id: 3164f585d548ac68027d22b104f2d8100b2b6845 $\nGoes there\n", buf.ptr);

	git_buf_dispose(&buf);
	git_blob_free(blob);

}