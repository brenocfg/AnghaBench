#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* free ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct buf_writestream {TYPE_3__ base; TYPE_1__ buf; TYPE_2__ member_0; } ;
typedef  int /*<<< orphan*/  git_filter_list ;
typedef  int /*<<< orphan*/  git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_CRLF ; 
 int /*<<< orphan*/  GIT_FILTER_TO_ODB ; 
 int /*<<< orphan*/  buf_writestream_close ; 
 int /*<<< orphan*/  buf_writestream_free ; 
 int /*<<< orphan*/  buf_writestream_write ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filter_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_list_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filter_list_stream_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/ * git_filter_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void test_filter_file__apply_stream(void)
{
	git_filter_list *fl;
	git_filter *crlf;
	struct buf_writestream write_target = { {
		buf_writestream_write,
		buf_writestream_close,
		buf_writestream_free } };

	cl_git_pass(git_filter_list_new(
		&fl, g_repo, GIT_FILTER_TO_ODB, 0));

	crlf = git_filter_lookup(GIT_FILTER_CRLF);
	cl_assert(crlf != NULL);

	cl_git_pass(git_filter_list_push(fl, crlf, NULL));

	cl_git_pass(git_filter_list_stream_file(fl, g_repo, "all-crlf", &write_target.base));
	cl_assert_equal_s("crlf\ncrlf\ncrlf\ncrlf\n", write_target.buf.ptr);

	git_filter_list_free(fl);
	write_target.base.free(&write_target.base);
}