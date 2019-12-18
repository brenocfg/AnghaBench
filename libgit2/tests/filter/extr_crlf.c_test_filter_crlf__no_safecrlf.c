#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_filter_list ;
typedef  int /*<<< orphan*/  git_filter ;
struct TYPE_6__ {char* ptr; void* size; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_FILTER_CRLF ; 
 int /*<<< orphan*/  GIT_FILTER_TO_ODB ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_filter_list_apply_to_data (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filter_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_list_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_filter_lookup (int /*<<< orphan*/ ) ; 
 void* strlen (char*) ; 

void test_filter_crlf__no_safecrlf(void)
{
	git_filter_list *fl;
	git_filter *crlf;
	git_buf in = {0}, out = GIT_BUF_INIT;

	cl_git_pass(git_filter_list_new(
		&fl, g_repo, GIT_FILTER_TO_ODB, 0));

	crlf = git_filter_lookup(GIT_FILTER_CRLF);
	cl_assert(crlf != NULL);

	cl_git_pass(git_filter_list_push(fl, crlf, NULL));

	/* Normalized \r\n succeeds with safecrlf */
	in.ptr = "Normal\r\nCRLF\r\nline-endings.\r\n";
	in.size = strlen(in.ptr);

	cl_git_pass(git_filter_list_apply_to_data(&out, fl, &in));
	cl_assert_equal_s("Normal\nCRLF\nline-endings.\n", out.ptr);

	/* Mix of line endings fails with safecrlf */
	in.ptr = "Mixed\nup\r\nLF\nand\r\nCRLF\nline-endings.\r\n";
	in.size = strlen(in.ptr);

	cl_git_pass(git_filter_list_apply_to_data(&out, fl, &in));
	cl_assert_equal_s("Mixed\nup\nLF\nand\nCRLF\nline-endings.\n", out.ptr);

	/* Normalized \n fails with safecrlf */
	in.ptr = "Normal\nLF\nonly\nline-endings.\n";
	in.size = strlen(in.ptr);

	cl_git_pass(git_filter_list_apply_to_data(&out, fl, &in));
	cl_assert_equal_s("Normal\nLF\nonly\nline-endings.\n", out.ptr);

	git_filter_list_free(fl);
	git_buf_dispose(&out);
}