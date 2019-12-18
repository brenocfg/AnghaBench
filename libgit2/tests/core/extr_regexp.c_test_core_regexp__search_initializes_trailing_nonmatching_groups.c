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
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ git_regmatch ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_compile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_search (int /*<<< orphan*/ *,char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  regex ; 

void test_core_regexp__search_initializes_trailing_nonmatching_groups(void)
{
	git_regmatch matches[3];

	cl_git_pass(git_regexp_compile(&regex, "(a)bc", 0));
	cl_git_pass(git_regexp_search(&regex, "abc", 3, matches));
	cl_assert_equal_i(matches[0].start, 0);
	cl_assert_equal_i(matches[0].end, 3);
	cl_assert_equal_i(matches[1].start, 0);
	cl_assert_equal_i(matches[1].end, 1);
	cl_assert_equal_i(matches[2].start, -1);
	cl_assert_equal_i(matches[2].end, -1);
}