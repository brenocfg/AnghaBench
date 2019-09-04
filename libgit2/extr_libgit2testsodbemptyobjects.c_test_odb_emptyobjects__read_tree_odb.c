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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_odb ; 
 int /*<<< orphan*/  git_odb_object_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_odb_emptyobjects__read_tree_odb(void)
{
	git_oid id;
	git_odb_object *tree_odb;

	cl_git_pass(git_oid_fromstr(&id, "4b825dc642cb6eb9a060e54bf8d69288fbee4904"));
	cl_git_pass(git_odb_read(&tree_odb, g_odb, &id));
	cl_assert(git_odb_object_data(tree_odb));
	cl_assert_equal_s("", git_odb_object_data(tree_odb));
	cl_assert_equal_i(0, git_odb_object_size(tree_odb));
	git_odb_object_free(tree_odb);
}