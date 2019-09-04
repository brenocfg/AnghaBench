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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * repo ; 
 int /*<<< orphan*/ * tree ; 

void test_object_tree_frompath__initialize(void)
{
	git_oid id;
	const char *tree_with_subtrees_oid = "ae90f12eea699729ed24555e40b9fd669da12a12";

	cl_git_pass(git_repository_open(&repo, cl_fixture("testrepo.git")));
	cl_assert(repo != NULL);

	cl_git_pass(git_oid_fromstr(&id, tree_with_subtrees_oid));
	cl_git_pass(git_tree_lookup(&tree, repo, &id));
	cl_assert(tree != NULL);
}