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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  git_commit_create_v (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_level (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_default (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_repo_init__init_with_initial_commit(void)
{
	git_index *index;

	cl_set_cleanup(&cleanup_repository, "committed");

	/* Initialize the repository */
	cl_git_pass(git_repository_init(&_repo, "committed", 0));

	/* Index will be automatically created when requested for a new repo */
	cl_git_pass(git_repository_index(&index, _repo));

	/* Create a file so we can commit it
	 *
	 * If you are writing code outside the test suite, you can create this
	 * file any way that you like, such as:
	 *      FILE *fp = fopen("committed/file.txt", "w");
	 *      fputs("some stuff\n", fp);
	 *      fclose(fp);
	 * We like to use the help functions because they do error detection
	 * in a way that's easily compatible with our test suite.
	 */
	cl_git_mkfile("committed/file.txt", "some stuff\n");

	/* Add file to the index */
	cl_git_pass(git_index_add_bypath(index, "file.txt"));
	cl_git_pass(git_index_write(index));

	/* Intentionally not using cl_repo_commit_from_index here so this code
	 * can be used as an example of how an initial commit is typically
	 * made to a repository...
	 */

	/* Make sure we're ready to use git_signature_default :-) */
	{
		git_config *cfg, *local;
		cl_git_pass(git_repository_config(&cfg, _repo));
		cl_git_pass(git_config_open_level(&local, cfg, GIT_CONFIG_LEVEL_LOCAL));
		cl_git_pass(git_config_set_string(local, "user.name", "Test User"));
		cl_git_pass(git_config_set_string(local, "user.email", "t@example.com"));
		git_config_free(local);
		git_config_free(cfg);
	}

	/* Create a commit with the new contents of the index */
	{
		git_signature *sig;
		git_oid tree_id, commit_id;
		git_tree *tree;

		cl_git_pass(git_signature_default(&sig, _repo));
		cl_git_pass(git_index_write_tree(&tree_id, index));
		cl_git_pass(git_tree_lookup(&tree, _repo, &tree_id));

		cl_git_pass(git_commit_create_v(
			&commit_id, _repo, "HEAD", sig, sig,
			NULL, "First", tree, 0));

		git_tree_free(tree);
		git_signature_free(sig);
	}

	git_index_free(index);
}