#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_index_write_tree_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_reset_hard__switch_file_to_dir(void)
{
	git_index_entry entry = {{ 0 }};
	git_index *idx;
	git_odb *odb;
	git_object *commit;
	git_tree *tree;
	git_signature *sig;
	git_oid src_tree_id, tgt_tree_id;
	git_oid src_id, tgt_id;

	cl_git_pass(git_repository_odb(&odb, repo));
	cl_git_pass(git_odb_write(&entry.id, odb, "", 0, GIT_OBJECT_BLOB));
	git_odb_free(odb);

	entry.mode = GIT_FILEMODE_BLOB;
	cl_git_pass(git_index_new(&idx));
	cl_git_pass(git_signature_now(&sig, "foo", "bar"));

	/* Create the old tree */
	entry.path = "README";
	cl_git_pass(git_index_add(idx, &entry));
	entry.path = "dir";
	cl_git_pass(git_index_add(idx, &entry));

	cl_git_pass(git_index_write_tree_to(&src_tree_id, idx, repo));
	cl_git_pass(git_index_clear(idx));

	cl_git_pass(git_tree_lookup(&tree, repo, &src_tree_id));
	cl_git_pass(git_commit_create(&src_id, repo, NULL, sig, sig, NULL, "foo", tree, 0, NULL));
	git_tree_free(tree);

	/* Create the new tree */
	entry.path = "README";
	cl_git_pass(git_index_add(idx, &entry));
	entry.path = "dir/FILE";
	cl_git_pass(git_index_add(idx, &entry));

	cl_git_pass(git_index_write_tree_to(&tgt_tree_id, idx, repo));
	cl_git_pass(git_tree_lookup(&tree, repo, &tgt_tree_id));
	cl_git_pass(git_commit_create(&tgt_id, repo, NULL, sig, sig, NULL, "foo", tree, 0, NULL));
	git_tree_free(tree);
	git_index_free(idx);
	git_signature_free(sig);

	/* Let's go to a known state of the src commit with the file named 'dir' */
	cl_git_pass(git_object_lookup(&commit, repo, &src_id, GIT_OBJECT_COMMIT));
	cl_git_pass(git_reset(repo, commit, GIT_RESET_HARD, NULL));
	git_object_free(commit);

	/* And now we move over to the commit with the directory named 'dir' */
	cl_git_pass(git_object_lookup(&commit, repo, &tgt_id, GIT_OBJECT_COMMIT));
	cl_git_pass(git_reset(repo, commit, GIT_RESET_HARD, NULL));
	git_object_free(commit);
}