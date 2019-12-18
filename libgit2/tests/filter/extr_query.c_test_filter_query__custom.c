#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_VERSION ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_for (char*,char*) ; 
 int /*<<< orphan*/  git_filter_register (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_filter_unregister (char*) ; 

void test_filter_query__custom(void)
{
	git_filter custom = { GIT_FILTER_VERSION };

	cl_git_pass(git_filter_register(
		"custom", &custom, 42));

	cl_assert_equal_i(1, filter_for("foo.custom", "crlf"));
	cl_assert_equal_i(1, filter_for("foo.custom", "ident"));
	cl_assert_equal_i(1, filter_for("foo.custom", "custom"));

	git_filter_unregister("custom");
}