#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  BIGFILE ; 
 int /*<<< orphan*/  BIGFILE_SIZE ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cl_assert_ (int,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_env_set (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_tree_entry_byname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_to_object (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int /*<<< orphan*/  p_fallocate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int p_open (int /*<<< orphan*/ ,int,int) ; 

void test_object_tree_read__largefile(void)
{
	git_reference *ref;
	git_commit *commit;
	git_tree *tree;
	git_oid oid;
	const git_tree_entry *entry;
	git_object *object;
	git_buf file = GIT_BUF_INIT;
	int fd;
	git_index *idx;

	if (!cl_is_env_set("GITTEST_INVASIVE_FS_SIZE"))
		cl_skip();

	cl_git_pass(git_reference_lookup(&ref, g_repo, "refs/heads/master"));
	cl_git_pass(git_repository_index(&idx, g_repo));

	cl_git_pass(git_buf_puts(&file, git_repository_workdir(g_repo)));
	cl_git_pass(git_buf_joinpath(&file, file.ptr, BIGFILE));

	fd = p_open(git_buf_cstr(&file), O_CREAT|O_RDWR, 0644);
	cl_assert_(fd >= 0, "invalid file descriptor");

	cl_must_pass(p_fallocate(fd, 0, BIGFILE_SIZE));
	cl_must_pass(p_close(fd));

	cl_git_pass(git_index_add_bypath(idx, BIGFILE));
	cl_repo_commit_from_index(&oid, g_repo, NULL, 0, "bigfile");

	cl_git_pass(git_commit_lookup(&commit, g_repo, &oid));
	cl_git_pass(git_commit_tree(&tree, commit));

	entry = git_tree_entry_byname(tree, BIGFILE);
	cl_assert_(entry, "entry was NULL");

	cl_git_pass(git_tree_entry_to_object(&object, g_repo, entry));

	git_buf_dispose(&file);
	git_object_free(object);
	git_tree_free(tree);
	git_index_free(idx);
	git_commit_free(commit);
	git_reference_free(ref);
}