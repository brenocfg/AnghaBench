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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_fromstrn (int /*<<< orphan*/ *,char const*,size_t) ; 
 size_t strlen (char const*) ; 

git_tree *resolve_commit_oid_to_tree(
	git_repository *repo,
	const char *partial_oid)
{
	size_t len = strlen(partial_oid);
	git_oid oid;
	git_object *obj = NULL;
	git_tree *tree = NULL;

	if (git_oid_fromstrn(&oid, partial_oid, len) == 0)
		cl_git_pass(git_object_lookup_prefix(&obj, repo, &oid, len, GIT_OBJECT_ANY));

	cl_git_pass(git_object_peel((git_object **) &tree, obj, GIT_OBJECT_TREE));
	git_object_free(obj);
	return tree;
}