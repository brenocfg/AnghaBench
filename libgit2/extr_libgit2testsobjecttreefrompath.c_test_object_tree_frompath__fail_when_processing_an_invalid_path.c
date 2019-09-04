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
typedef  int /*<<< orphan*/  git_tree_entry ;

/* Variables and functions */
 int /*<<< orphan*/  cl_must_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tree ; 

void test_object_tree_frompath__fail_when_processing_an_invalid_path(void)
{
	git_tree_entry *e;

	cl_must_fail(git_tree_entry_bypath(&e, tree, "/"));
	cl_must_fail(git_tree_entry_bypath(&e, tree, "/ab"));
	cl_must_fail(git_tree_entry_bypath(&e, tree, "/ab/de"));
	cl_must_fail(git_tree_entry_bypath(&e, tree, "ab//de"));
}