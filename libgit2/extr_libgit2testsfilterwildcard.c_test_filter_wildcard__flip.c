#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_filter_list ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_LEN ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_FILTER_TO_ODB ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flipped ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_list_apply_to_data (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filter_list_load (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ input ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_filter_wildcard__flip(void)
{
	git_filter_list *fl;
	git_buf in = GIT_BUF_INIT, out = GIT_BUF_INIT;

	cl_git_pass(git_filter_list_load(
		&fl, g_repo, NULL, "hero-flip-foo", GIT_FILTER_TO_ODB, 0));

	cl_git_pass(git_buf_put(&in, (char *)input, DATA_LEN));
	cl_git_pass(git_filter_list_apply_to_data(&out, fl, &in));

	cl_assert_equal_i(DATA_LEN, out.size);

	cl_assert_equal_i(
		0, memcmp(flipped, out.ptr, out.size));

	git_filter_list_free(fl);
	git_buf_dispose(&out);
	git_buf_dispose(&in);
}