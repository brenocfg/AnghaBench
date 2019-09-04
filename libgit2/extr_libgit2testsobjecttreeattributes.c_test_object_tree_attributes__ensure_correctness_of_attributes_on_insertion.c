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
typedef  int /*<<< orphan*/  git_treebuilder ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_filemode_t ;

/* Variables and functions */
 int /*<<< orphan*/  blob_oid ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_object_tree_attributes__ensure_correctness_of_attributes_on_insertion(void)
{
	git_treebuilder *builder;
	git_oid oid;

	cl_git_pass(git_oid_fromstr(&oid, blob_oid));

	cl_git_pass(git_treebuilder_new(&builder, repo, NULL));

	cl_git_fail(git_treebuilder_insert(NULL, builder, "one.txt", &oid, (git_filemode_t)0777777));
	cl_git_fail(git_treebuilder_insert(NULL, builder, "one.txt", &oid, (git_filemode_t)0100666));
	cl_git_fail(git_treebuilder_insert(NULL, builder, "one.txt", &oid, (git_filemode_t)0000001));

	git_treebuilder_free(builder);
}