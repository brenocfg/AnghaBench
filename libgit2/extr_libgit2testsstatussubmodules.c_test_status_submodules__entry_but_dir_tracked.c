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
typedef  int /*<<< orphan*/  git_status_list ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_status_submodules__entry_but_dir_tracked(void)
{
	git_repository *repo;
	git_status_list *status;
	git_diff *diff;
	git_index *index;
	git_tree *tree;

	cl_git_pass(git_repository_init(&repo, "mixed-submodule", 0));
	cl_git_mkfile("mixed-submodule/.gitmodules", "[submodule \"sub\"]\n path = sub\n url = ../foo\n");
	cl_git_pass(p_mkdir("mixed-submodule/sub", 0777));
	cl_git_mkfile("mixed-submodule/sub/file", "");

	/* Create the commit with sub/file as a file, and an entry for sub in the modules list */
	{
		git_oid tree_id, commit_id;
		git_signature *sig;
		git_reference *ref;

		cl_git_pass(git_repository_index(&index, repo));
		cl_git_pass(git_index_add_bypath(index, ".gitmodules"));
		cl_git_pass(git_index_add_bypath(index, "sub/file"));
		cl_git_pass(git_index_write(index));
		cl_git_pass(git_index_write_tree(&tree_id, index));
		cl_git_pass(git_signature_now(&sig, "Sloppy Submoduler", "sloppy@example.com"));
		cl_git_pass(git_tree_lookup(&tree, repo, &tree_id));
		cl_git_pass(git_commit_create(&commit_id, repo, NULL, sig, sig, NULL, "message", tree, 0, NULL));
		cl_git_pass(git_reference_create(&ref, repo, "refs/heads/master", &commit_id, 1, "commit: foo"));
		git_reference_free(ref);
		git_signature_free(sig);
	}

	cl_git_pass(git_diff_tree_to_index(&diff, repo, tree, index, NULL));
	cl_assert_equal_i(0, git_diff_num_deltas(diff));
	git_diff_free(diff);

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, index, NULL));
	cl_assert_equal_i(0, git_diff_num_deltas(diff));
	git_diff_free(diff);

	cl_git_pass(git_status_list_new(&status, repo, NULL));
	cl_assert_equal_i(0, git_status_list_entrycount(status));

	git_status_list_free(status);
	git_index_free(index);
	git_tree_free(tree);
	git_repository_free(repo);
}