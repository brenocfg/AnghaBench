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
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_table ; 
 int /*<<< orphan*/  git_strmap_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_strmap_set (int /*<<< orphan*/ ,char*,char*) ; 

void test_core_strmap__set_persists_multpile_keys(void)
{
	cl_git_pass(git_strmap_set(g_table, "foo", "oof"));
	cl_git_pass(git_strmap_set(g_table, "bar", "rab"));
	cl_assert_equal_s(git_strmap_get(g_table, "foo"), "oof");
	cl_assert_equal_s(git_strmap_get(g_table, "bar"), "rab");
}