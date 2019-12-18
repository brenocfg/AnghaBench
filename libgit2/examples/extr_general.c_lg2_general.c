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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  blob_parsing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_error (int,char*) ; 
 int /*<<< orphan*/  commit_parsing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commit_writing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_files (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_libgit2_init () ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  index_walking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_database (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_parsing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reference_listing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revwalking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tag_parsing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_parsing (int /*<<< orphan*/ *) ; 

int lg2_general(git_repository *repo, int argc, char** argv)
{
	int error;
	git_oid oid;
	char *repo_path;

	/**
	 * Initialize the library, this will set up any global state which libgit2 needs
	 * including threading and crypto
	 */
	git_libgit2_init();

	/**
	 * ### Opening the Repository
	 *
	 * There are a couple of methods for opening a repository, this being the
	 * simplest.  There are also [methods][me] for specifying the index file
	 * and work tree locations, here we assume they are in the normal places.
	 *
	 * (Try running this program against tests/resources/testrepo.git.)
	 *
	 * [me]: http://libgit2.github.com/libgit2/#HEAD/group/repository
	 */
	repo_path = (argc > 1) ? argv[1] : "/opt/libgit2-test/.git";

	error = git_repository_open(&repo, repo_path);
	check_error(error, "opening repository");

	oid_parsing(&oid);
	object_database(repo, &oid);
	commit_writing(repo);
	commit_parsing(repo);
	tag_parsing(repo);
	tree_parsing(repo);
	blob_parsing(repo);
	revwalking(repo);
	index_walking(repo);
	reference_listing(repo);
	config_files(repo_path, repo);

	/**
	 * Finally, when you're done with the repository, you can free it as well.
	 */
	git_repository_free(repo);

	return 0;
}