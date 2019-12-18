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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_index_read_tree__read_write_involution(void)
{
	git_repository *repo;
	git_index *index;
	git_oid tree_oid;
	git_tree *tree;
	git_oid expected;

	p_mkdir("read_tree", 0700);

	cl_git_pass(git_repository_init(&repo, "./read_tree", 0));
	cl_git_pass(git_repository_index(&index, repo));

	cl_assert(git_index_entrycount(index) == 0);

	p_mkdir("./read_tree/abc", 0700);

	/* Sort order: '-' < '/' < '_' */
	cl_git_mkfile("./read_tree/abc-d", NULL);
	cl_git_mkfile("./read_tree/abc/d", NULL);
	cl_git_mkfile("./read_tree/abc_d", NULL);

	cl_git_pass(git_index_add_bypath(index, "abc-d"));
	cl_git_pass(git_index_add_bypath(index, "abc_d"));
	cl_git_pass(git_index_add_bypath(index, "abc/d"));

	/* write-tree */
	cl_git_pass(git_index_write_tree(&expected, index));

	/* read-tree */
	git_tree_lookup(&tree, repo, &expected);
	cl_git_pass(git_index_read_tree(index, tree));
	git_tree_free(tree);

	cl_git_pass(git_index_write_tree(&tree_oid, index));
	cl_assert_equal_oid(&expected, &tree_oid);

	git_index_free(index);
	git_repository_free(repo);

	cl_fixture_cleanup("read_tree");
}