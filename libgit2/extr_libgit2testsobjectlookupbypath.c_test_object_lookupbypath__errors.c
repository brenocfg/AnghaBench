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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_actualobject ; 
 scalar_t__ g_root_tree ; 
 int /*<<< orphan*/  git_object_lookup_bypath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void test_object_lookupbypath__errors(void)
{
	cl_assert_equal_i(GIT_EINVALIDSPEC,
			git_object_lookup_bypath(&g_actualobject, (git_object*)g_root_tree,
				"subdir/subdir_test2.txt", GIT_OBJECT_TREE)); /* It's not a tree */
	cl_assert_equal_i(GIT_ENOTFOUND,
			git_object_lookup_bypath(&g_actualobject, (git_object*)g_root_tree,
				"file/doesnt/exist", GIT_OBJECT_ANY));
}