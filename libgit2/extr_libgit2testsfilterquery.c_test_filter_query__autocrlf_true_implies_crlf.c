#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  filter_for (char*,char*) ; 
 int /*<<< orphan*/  g_repo ; 

void test_filter_query__autocrlf_true_implies_crlf(void)
{
	cl_repo_set_bool(g_repo, "core.autocrlf", true);
	cl_assert_equal_i(1, filter_for("not_in_gitattributes", "crlf"));
	cl_assert_equal_i(1, filter_for("foo.txt", "crlf"));
	cl_assert_equal_i(0, filter_for("foo.bin", "crlf"));
	cl_assert_equal_i(1, filter_for("foo.lf", "crlf"));

	cl_repo_set_bool(g_repo, "core.autocrlf", false);
	cl_assert_equal_i(0, filter_for("not_in_gitattributes", "crlf"));
	cl_assert_equal_i(1, filter_for("foo.txt", "crlf"));
	cl_assert_equal_i(0, filter_for("foo.bin", "crlf"));
	cl_assert_equal_i(1, filter_for("foo.lf", "crlf"));
}