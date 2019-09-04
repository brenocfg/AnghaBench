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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int git_filemode_t ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * git_tree_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_tree_entry_filemode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_id (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tree_checker(
	git_oid *tid,
	const char *expected_sha,
	git_filemode_t expected_filemode)
{
	git_tree *tree;
	const git_tree_entry *entry;
	git_oid oid;

	cl_git_pass(git_tree_lookup(&tree, _repo, tid));
	cl_assert_equal_i(1, (int)git_tree_entrycount(tree));
	entry = git_tree_entry_byindex(tree, 0);

	cl_git_pass(git_oid_fromstr(&oid, expected_sha));

	cl_assert_equal_i(0, git_oid_cmp(&oid, git_tree_entry_id(entry)));
	cl_assert_equal_i(expected_filemode, git_tree_entry_filemode(entry));

	git_tree_free(tree);
}